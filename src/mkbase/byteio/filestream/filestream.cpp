#include "filestream.hpp"

std::expected<monokuma::byteio::FileStream, monokuma::error::Error> monokuma::byteio::FileStream::from_stream(std::fstream &&stream) {
    if (!stream.is_open())
        return std::unexpected(error::Error(std::runtime_error("Failed top create FileStream from stream: stream is closed")));
    stream.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);
    return FileStream(std::move(stream));
}

std::expected<monokuma::byteio::FileStream, monokuma::error::Error> monokuma::byteio::FileStream::from_file(const std::filesystem::path &file) {
    std::fstream stream(file, std::ios::in | std::ios::out | std::ios::binary);
    if (!stream.is_open())
        return std::unexpected(error::Error(std::runtime_error("Failed to create FileStream from file: failed to open file")));
    stream.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);
    return FileStream(std::move(stream));
}