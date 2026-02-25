#include "byteio.hpp"

#include <bit>

monokuma::byteio::i32 monokuma::byteio::merge_bytes_to_i32(const std::array<byte, 4> &bytes) {
    return static_cast<i32>(bytes[3]) << 24
    | static_cast<i32>(bytes[2]) << 16
    | static_cast<i32>(bytes[1]) << 8
    | static_cast<i32>(bytes[0]);
}

monokuma::byteio::i64 monokuma::byteio::merge_bytes_to_i64(const std::array<byte, 8> &bytes) {
    return static_cast<i64>(bytes[7]) << 56
    | static_cast<i64>(bytes[6]) << 48
    | static_cast<i64>(bytes[5]) << 40
    | static_cast<i64>(bytes[4]) << 32
    | static_cast<i64>(bytes[3]) << 24
    | static_cast<i64>(bytes[2]) << 16
    | static_cast<i64>(bytes[1]) << 8
    | static_cast<i64>(bytes[0]);

}
