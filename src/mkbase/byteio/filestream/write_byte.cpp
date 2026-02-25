#include "filestream.hpp"

std::optional<monokuma::error::Error> monokuma::byteio::FileStream::write_byte(const byte &byte) {
    try { this->stream_.put(byte); }
    catch (const std::ios_base::failure& write_error) { return error::Error(std::runtime_error("Failed to write byte:")) + error::Error(write_error); }
    this->stream_.flush();
    return std::nullopt;
}