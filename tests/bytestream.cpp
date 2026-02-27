#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/mkbase.hpp>

struct JustAStruct {
    monokuma::byteio::i64 int64_value = 35;
    monokuma::byteio::i32 int32_value = 12;
    std::array<char, 4> some_raw_data = { 'A', 'G', 'A', 'R' };
    bool flag = true;
};

TEST_CASE_METHOD(JustAStruct, "Write") {
    auto bytestream = monokuma::byteio::ByteStream();
    REQUIRE(!bytestream.write(JustAStruct{}));
    REQUIRE(bytestream.size() == 24);
}

TEST_CASE_METHOD(JustAStruct, "Read") {
    auto bytestream = monokuma::byteio::ByteStream({
        0b00000011, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
        0b00000100, 0b00000000, 0b00000000, 0b00000000, 'H', 'o', 'l', 'a',
        0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    });

    JustAStruct buffer;
    REQUIRE(!bytestream.read(&buffer));
    REQUIRE(buffer.int64_value == 3);
    REQUIRE(buffer.int32_value == 4);
    REQUIRE(buffer.some_raw_data == std::array{ 'H', 'o', 'l', 'a' });
    REQUIRE(buffer.flag == true);
}