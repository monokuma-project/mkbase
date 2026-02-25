#include "bytesarray.hpp"

std::optional<monokuma::error::Error> monokuma::byteio::BytesArray::write_byte(const byte &byte) {
    try { this->bytes_.at(this->reader_position_++) = byte; }
    catch (const std::out_of_range& oor_error) { return error::Error(std::runtime_error("Failed to write byte:")) + error::Error(oor_error); }
    return std::nullopt;
}