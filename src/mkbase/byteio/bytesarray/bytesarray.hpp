#pragma once

#include "../bytestream/bytestream.hpp"

#include <vector>

#include "mkbase/api.hpp"
#include "mkbase/error/error.hpp"
#include "mkbase/byteio/types.hpp"

namespace monokuma::byteio {
    class MKBASE_API BytesArray {
        std::vector<byte> bytes_;
        std::size_t reader_position_ = 0;
    public:
        BytesArray(const std::size_t& reserve) { this->bytes_.resize(reserve); }
        BytesArray(const std::vector<byte>& bytes) { this->bytes_ = bytes; }
        BytesArray(std::vector<byte>&& bytes) { this->bytes_ = std::move(bytes); }

        BytesArray() = delete;

        std::expected<byte, error::Error> read_byte();

        std::size_t get_position() const { return this->reader_position_; }
        BytesArray& set_position(const std::size_t& new_position) { this->reader_position_ = new_position; return *this; }

        std::optional<error::Error> write_byte(const byte& byte);

        const std::vector<byte>& get_bytes() const { return this->bytes_; }
    };
}

template <> struct MKBASE_API monokuma::byteio::impl::is_byte_stream_source_provider<monokuma::byteio::BytesArray> : std::true_type {};