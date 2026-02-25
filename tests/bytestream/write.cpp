#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/byteio/byteio.hpp>

TEST_CASE("ByteStream write operations", "[bytesarray]") {
    SECTION("Write byte through BytesArray") {
        auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        })));

        {
            auto result = bytes.write_byte('H');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[0] == 'H');
        }

        {
            auto result = bytes.write_byte('e');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[1] == 'e');
        }

        {
            auto result = bytes.write_byte('l');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[2] == 'l');
        }

        {
            auto result = bytes.write_byte('l');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[3] == 'l');
        }

        {
            auto result = bytes.write_byte('o');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[4] == 'o');
        }

        {
            auto result = bytes.write_byte(' ');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[5] == ' ');
        }

        {
            auto result = bytes.write_byte('W');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[6] == 'W');
        }

        {
            auto result = bytes.write_byte('o');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[7] == 'o');
        }

        {
            auto result = bytes.write_byte('r');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[8] == 'r');
        }

        {
            auto result = bytes.write_byte('l');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[9] == 'l');
        }

        {
            auto result = bytes.write_byte('d');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[10] == 'd');
        }

        {
            auto result = bytes.write_byte('!');
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[11] == '!');
        }
    }

    SECTION("Write int32 through BytesArray") {
        auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
            0b00001000,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00000100,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00000010,
            0b00000000,
            0b00000000,
            0b00000000,
        })));

        {
            auto result = bytes.write_int32(2);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[0] == 0b00000010);
            REQUIRE(bytes.source_provider().get_bytes()[1] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[2] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[3] == 0b00000000);
        }

        {
            auto result = bytes.write_int32(4);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[4] == 0b00000100);
            REQUIRE(bytes.source_provider().get_bytes()[5] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[6] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[7] == 0b00000000);
        }

        {
            auto result = bytes.write_int32(8);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[8] == 0b00001000);
            REQUIRE(bytes.source_provider().get_bytes()[9] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[10] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[11] == 0b00000000);
        }
    }

    SECTION("Write int64 through BytesArray") {
        auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
            0b00001000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00000100,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00000010,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
        })));

        {
            auto result = bytes.write_int64(2);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[0] == 0b00000010);
            REQUIRE(bytes.source_provider().get_bytes()[1] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[2] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[3] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[4] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[5] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[6] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[7] == 0b00000000);
        }

        {
            auto result = bytes.write_int64(4);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[8] == 0b00000100);
            REQUIRE(bytes.source_provider().get_bytes()[9] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[10] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[11] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[12] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[13] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[14] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[15] == 0b00000000);
        }

        {
            auto result = bytes.write_int64(8);
            REQUIRE(!result.has_value());
            REQUIRE(bytes.source_provider().get_bytes()[16] == 0b00001000);
            REQUIRE(bytes.source_provider().get_bytes()[17] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[18] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[19] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[20] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[21] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[22] == 0b00000000);
            REQUIRE(bytes.source_provider().get_bytes()[23] == 0b00000000);
        }
    }
}