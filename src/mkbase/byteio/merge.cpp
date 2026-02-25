#include "byteio.hpp"

#include <bit>

monokuma::byteio::i32 monokuma::byteio::merge_bytes_to_i32(const std::array<byte, 4> &bytes) {
    auto result = (static_cast<i32>(bytes[0]) << 24)
    | (static_cast<i32>(bytes[1]) << 16)
    | (static_cast<i32>(bytes[2]) << 8)
    | (static_cast<i32>(bytes[3]));

    if constexpr (std::endian::native == std::endian::little)
        return static_cast<i32>(std::byteswap(result));
    else return static_cast<i32>(result);
}

monokuma::byteio::i64 monokuma::byteio::merge_bytes_to_i64(const std::array<byte, 8> &bytes) {
    auto result = (static_cast<byte_view>(bytes[0]).to_ullong() << 56)
    | (static_cast<byte_view>(bytes[1]).to_ullong() << 48)
    | (static_cast<byte_view>(bytes[2]).to_ullong() << 40)
    | (static_cast<byte_view>(bytes[3]).to_ullong() << 32)
    | (static_cast<byte_view>(bytes[4]).to_ullong() << 24)
    | (static_cast<byte_view>(bytes[5]).to_ullong() << 16)
    | (static_cast<byte_view>(bytes[6]).to_ullong() << 8)
    | (static_cast<byte_view>(bytes[7]).to_ullong());

    if constexpr (std::endian::native == std::endian::little)
        return static_cast<i64>(std::byteswap(result));
    else return static_cast<i64>(result);
}
