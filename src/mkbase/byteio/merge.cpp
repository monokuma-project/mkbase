#include "byteio.hpp"

#include <bit>

monokuma::byteio::i32 monokuma::byteio::merge_bytes_to_i32(const std::array<byte, 4> &bytes) {
     const auto result = static_cast<i32>(bytes[0]) << 24
    | static_cast<i32>(bytes[1]) << 16
    | static_cast<i32>(bytes[2]) << 8
    | static_cast<i32>(bytes[3]);

    if constexpr (std::endian::native == std::endian::little)
        return std::byteswap(result);
    else return result;
}

monokuma::byteio::i64 monokuma::byteio::merge_bytes_to_i64(const std::array<byte, 8> &bytes) {
    const auto result = static_cast<i64>(bytes[0]) << 56
    | static_cast<i64>(bytes[1]) << 48
    | static_cast<i64>(bytes[2]) << 40
    | static_cast<i64>(bytes[3]) << 32
    | static_cast<i64>(bytes[4]) << 24
    | static_cast<i64>(bytes[5]) << 16
    | static_cast<i64>(bytes[6]) << 8
    | static_cast<i64>(bytes[7]);

    if constexpr (std::endian::native == std::endian::little)
        return std::byteswap(result);
    else return result;
}
