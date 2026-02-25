#include "bytesarray.hpp"

std::expected<monokuma::byteio::byte, monokuma::error::Error> monokuma::byteio::BytesArray::read_byte() {
    try { return this->bytes_.at(this->reader_position_++); }
    catch (const std::out_of_range& oor_error) { return std::unexpected(error::Error(std::runtime_error("Failed to read byte: ")) + error::Error(oor_error)); }
}