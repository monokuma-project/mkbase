#include "byteio.hpp"

std::array<monokuma::byteio::byte, 4> monokuma::byteio::separate_i32_to_bytes(const i32 &value) {
    std::array<byte, 4> result{};
    result[0] = (value) & 0xFF;
    result[1] = (value >> 8) & 0xFF;
    result[2] = (value >> 16) & 0xFF;
    result[3] = (value >> 24) & 0xFF;
    return result;
}

std::array<monokuma::byteio::byte, 8> monokuma::byteio::separate_i64_to_bytes(const i64 &value) {
    std::array<byte, 8> result{};
    result[0] = (value) & 0xFF;
    result[1] = (value >> 8) & 0xFF;
    result[2] = (value >> 16) & 0xFF;
    result[3] = (value >> 24) & 0xFF;
    result[4] = (value >> 32) & 0xFF;
    result[5] = (value >> 40) & 0xFF;
    result[6] = (value >> 48) & 0xFF;
    result[7] = (value >> 56) & 0xFF;
    return result;
}
