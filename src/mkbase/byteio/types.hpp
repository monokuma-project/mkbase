#pragma once

#include <bitset>

namespace monokuma::byteio {
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using byte = std::uint8_t;
    using byte_view = std::bitset<8>;
}