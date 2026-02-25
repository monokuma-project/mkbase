#include "filestream.hpp"

std::expected<monokuma::byteio::byte, monokuma::error::Error> monokuma::byteio::FileStream::read_byte() {
    char byte;
    try { this->stream_.get(byte); }
    catch (const std::ios_base::failure& read_error) { return std::unexpected(error::Error(std::runtime_error("Failed to read byte:")) + error::Error(read_error)); }
    return byte;
}
