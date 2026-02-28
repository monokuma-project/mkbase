#pragma once

#include <expected>
#include <filesystem>
#include <fstream>

#include "mkbase/api.hpp"
#include "mkbase/error/error.hpp"
#include "mkbase/byteio/types.hpp"

namespace monokuma::byteio {
    class MKBASE_API LazyByteStream {
        std::fstream stream_;

        LazyByteStream(std::fstream&& stream) : stream_(std::move(stream)) {}
    public:
        LazyByteStream(const LazyByteStream&) = delete;
        LazyByteStream& operator=(const LazyByteStream&) = delete;

        LazyByteStream(LazyByteStream&& other) = default;
        LazyByteStream& operator=(LazyByteStream&& other) = default;

        ~LazyByteStream() { this->stream_.close(); }

        static std::expected<LazyByteStream, error::Error> from_stream(std::fstream&& stream) {
            if (stream.is_open()) return LazyByteStream(std::move(stream));
            return std::unexpected(MKERROR(std::runtime_error("Failed to create LazyByteStream: file is closed")));
        }

        static std::expected<LazyByteStream, error::Error> from_file(const std::filesystem::path& path) {
            auto flags = std::ios_base::in | std::ios::out | std::ios_base::binary;
            if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
                flags |= std::ios::trunc;
            std::fstream stream(path, flags);
            return LazyByteStream(std::move(stream));
        }

        template <class T> std::optional<error::Error> write(const T& value) {
            static_assert(std::is_trivially_copyable_v<T>, "Supported only trivially copyable types");

            const byte* data = reinterpret_cast<const byte*>(&value);
            this->stream_.write(reinterpret_cast<const char*>(data), sizeof(T));
            if (!this->stream_)
                return MKERROR(std::runtime_error("Failed to read" + std::string(typeid(T).name()) + ": unknown stream error"));
            return std::nullopt;
        }

        template <class AsT> std::optional<error::Error> read(AsT& buffer) {
            this->stream_.read(reinterpret_cast<char*>(&buffer), sizeof(AsT));
            if (this->stream_.gcount() != sizeof(AsT))
                return MKERROR(std::runtime_error("Faled to read " + std::string(typeid(AsT).name()) + ": gcount less than type size"));
            return std::nullopt;
        }

        template <class AsT> std::expected<AsT, error::Error> read() {
            AsT buffer;
            if (auto read_result = this->read(buffer); read_result)
                return MKERROR(read_result.value());
            return buffer;
        }

        [[nodiscard]] std::size_t position() { return this->stream_.tellg(); }
        LazyByteStream& position(const std::size_t& new_position, const std::ios_base::seekdir& at) {
            this->stream_.seekg(new_position, at);
            return *this;
        }
    };
}