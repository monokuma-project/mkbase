#pragma once

#include <array>
#include <expected>
#include <optional>
#include <vector>

#include "mkbase/api.hpp"
#include "mkbase/error/error.hpp"
#include "mkbase/byteio/types.hpp"

namespace monokuma::byteio {
    class MKBASE_API ByteStream {
        std::vector<byte> bytes_;
        std::size_t offset_;

        bool is_empty_position(const std::size_t& position) {
            return this->bytes_.empty() || position >= this->bytes_.size();
        }
    public:
        ByteStream(std::vector<byte>&& bytes, std::size_t offset = 0) : bytes_(std::move(bytes)), offset_(offset) {}
        ByteStream(std::vector<byte>& bytes, std::size_t offset = 0) : bytes_(bytes), offset_(offset) {}
        ByteStream(std::size_t offset = 0) : offset_(offset) {}

        template <class T> std::optional<error::Error> write(const T& value) {
            static_assert(std::is_trivially_copyable_v<T>, "Type is not trivially copyable");
            const byte* value_bytes = reinterpret_cast<const byte*>(&value);
            for (std::size_t i = 0; i < sizeof(T); ++i) {
                if (this->is_empty_position(this->offset_++))
                    this->bytes_.push_back(value_bytes[i]);
                else {
                    try { this->bytes_.at(this->offset_++) = value_bytes[i]; }
                    catch (const std::exception& error) {
                        return MKERRORE(std::runtime_error("[" + std::to_string(i) + "]: Failed to write byte:"), error);
                    }
                }
            }
            return std::nullopt;
        }

        template <class AsT> std::optional<error::Error> read(AsT* buffer) {
            if (this->offset_ + sizeof(AsT) - 1 >= this->bytes_.size())
                return MKERROR(std::out_of_range("Failed to read: out_of_range"));
            auto* buffer_bytes = reinterpret_cast<byte*>(buffer);
            for (std::size_t i = 0; i < sizeof(AsT); ++i) {
                try { buffer_bytes[i] = this->bytes_.at(this->offset_++); }
                catch (const std::exception& error) {
                    return MKERRORE(std::runtime_error("[" + std::to_string(i) + "]: Failed to read byte:"), error);
                }
            }
            return std::nullopt;
        }

        [[nodiscard]] std::size_t offset() const { return this->offset_; }
        ByteStream& offset(std::size_t new_offset) { this->offset_ = new_offset; return *this; }
        [[nodiscard]] std::size_t size() const { return this->bytes_.size(); }
        [[nodiscard]] std::size_t remaining() const { return this->bytes_.size() - this->offset_; }

        [[nodiscard]] const std::vector<byte>& bytes() const { return this->bytes_; }
    };
}