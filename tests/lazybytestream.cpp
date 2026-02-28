#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/mkbase.hpp>

struct JustAStruct {
    monokuma::byteio::i64 int64_value = 35;
    monokuma::byteio::i32 int32_value = 12;
    std::array<char, 4> some_raw_data = { 'A', 'G', 'A', 'R' };
    bool flag = true;
};

TEST_CASE("Write/Write", "[lazybytestream]") {
    SECTION("Write") {
        auto bytestream = monokuma::byteio::LazyByteStream::from_file("./test_tmp.bin");
        REQUIRE(bytestream);
        if (auto write_result = bytestream->write(JustAStruct{}); write_result) {
            INFO(write_result.value().what());
        } else {
            REQUIRE(bytestream->position() == 24);
        }
    }
}