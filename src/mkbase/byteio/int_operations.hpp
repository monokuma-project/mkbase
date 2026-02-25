#pragma once

#include "mkbase/api.hpp"
#include "types.hpp"

namespace monokuma::byteio {
    i32 MKBASE_API  merge_bytes_to_i32(const std::array<byte, 4>& bytes);
    i64 MKBASE_API merge_bytes_to_i64(const std::array<byte, 8>& bytes);

    std::array<byte, 4> MKBASE_API separate_i32_to_bytes(const i32& value);
    std::array<byte, 8> MKBASE_API separate_i64_to_bytes(const i64& value);
}