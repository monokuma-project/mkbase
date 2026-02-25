#pragma once

#include <expected>
#include <filesystem>
#include <fstream>

#include "mkbase/api.hpp"
#include "mkbase/byteio/bytestream/bytestream.hpp"
#include "mkbase/error/error.hpp"
#include "mkbase/byteio/types.hpp"

namespace monokuma::byteio {
    class MKBASE_API FileStream {
        std::fstream stream_;

        FileStream(std::fstream&& stream) : stream_(std::move(stream)) { this->stream_.seekg(0, std::ios::beg); this->stream_.seekp(0, std::ios::beg); }
    public:
        static std::expected<FileStream, error::Error> from_stream(std::fstream&& stream);
        static std::expected<FileStream, error::Error> from_file(const std::filesystem::path& file);

        std::expected<byte, error::Error> read_byte();

        FileStream& set_position(const std::size_t& new_position) {
            this->stream_.seekg(std::ios::beg, static_cast<std::ios_base::seekdir>(new_position));
            this->stream_.seekp(std::ios::beg, static_cast<std::ios_base::seekdir>(new_position));
            return *this;
        }

        std::optional<error::Error> write_byte(const byte& byte);
    };
}

template <> struct MKBASE_API monokuma::byteio::impl::is_byte_stream_source_provider<monokuma::byteio::FileStream> : std::true_type {};