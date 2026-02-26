#pragma once

#include <array>
#include <expected>
#include <optional>

#include "mkbase/api.hpp"
#include "mkbase/error/error.hpp"
#include "mkbase/byteio/int_operations.hpp"
#include "mkbase/byteio/types.hpp"

namespace monokuma::byteio {
    namespace impl {
        template <class> struct MKBASE_API is_byte_stream_source_provider : std::false_type {};
    }

    template <class T> concept is_byte_stream_source_provider = impl::is_byte_stream_source_provider<T>::value;

    template <is_byte_stream_source_provider SourceProviderT> class MKBASE_API ByteStream {
        SourceProviderT source_provider_;
    public:
        ByteStream(SourceProviderT&& source_provider) : source_provider_(std::move(source_provider)) {}

        ByteStream& offset(const std::size_t& new_offset) { this->source_provider_.set_position(new_offset); return *this; }
        std::size_t get_offset() const { return this->source_provider_.get_position(); }

        std::optional<error::Error> write_byte(const byte& byte) {
            if (auto result = this->source_provider_.write_byte(byte); result)
                return error::Error(std::runtime_error("Failed to write byte:")) + result.value();
            return std::nullopt;
        }

        std::optional<error::Error> write_int32(const i32& value) {
            auto bytes = separate_i32_to_bytes(value);
            for (const auto& byte : bytes)
                if (auto result = this->write_byte(byte); result)
                    return error::Error(std::runtime_error("Failed to write int32:")) + result.value();
            return std::nullopt;
        }

        std::optional<error::Error> write_int64(const i64& value) {
            auto bytes = separate_i64_to_bytes(value);
            for (const auto& byte : bytes)
                if (auto result = this->write_byte(byte); result)
                    return error::Error(std::runtime_error("Failed to write int64:")) + result.value();
            return std::nullopt;
        }


        std::expected<byte, error::Error> read_byte() {
            if (auto result = this->source_provider_.read_byte(); !result)
                return std::unexpected(error::Error(std::runtime_error("Failed to read byte: ")) + result.error());
            else return result.value();
        }

        std::expected<i32, error::Error> read_int32() {
            std::array<byte, 4> bytes_buf{};
            for (std::size_t i = 0; i < 4; ++i) {
                if (auto result = this->read_byte(); !result)
                    return std::unexpected(error::Error(std::runtime_error("Failed to read int32:")) + result.error());
                else bytes_buf[i] = result.value();
            }
            return merge_bytes_to_i32(bytes_buf);
        }

        std::expected<i64, error::Error> read_int64() {
            std::array<byte, 8> bytes_buf{};
            for (std::size_t i = 0; i < 8; ++i) {
                if (auto result = this->read_byte(); !result)
                    return std::unexpected(error::Error(std::runtime_error("Failed to read int64:")) + result.error());
                else bytes_buf[i] = result.value();
            }
            return merge_bytes_to_i64(bytes_buf);
        }


        SourceProviderT& source_provider() { return source_provider_; }
    };
}