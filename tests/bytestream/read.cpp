#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/byteio/byteio.hpp>

TEST_CASE("BytesStream read operations", "[bytesarray]") {
    SECTION("Read bytes from BytesArray") {
        {
            auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
                'H', 'e', 'l', 'l', 'o',
                ' ',
                'W', 'o', 'r', 'l', 'd', '!',
            })));

            for (std::size_t i = 0; i < bytes.source_provider().get_bytes().size(); ++i) {
                auto byte = bytes.read_byte();
                REQUIRE(byte.has_value());
                REQUIRE(byte.value() == bytes.source_provider().get_bytes()[i]);
            }
        }
    }

    SECTION("Read int32 from BytesArray") {
        auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
            0b00000010,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00000100,
            0b00000000,
            0b00000000,
            0b00000000,

            0b00001000,
            0b00000000,
            0b00000000,
            0b00000000,
        })));

        {
            auto result = bytes.read_int32();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 2);
        }

        {
            auto result = bytes.read_int32();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 4);
        }

        {
            auto result = bytes.read_int32();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 8);
        }
    }

    SECTION("Read int64 from BytesArray") {
        auto bytes = monokuma::byteio::ByteStream(std::move(monokuma::byteio::BytesArray({
            0b00000010,
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

            0b00001000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
        })));

        {
            auto result = bytes.read_int64();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 2);
        }

        {
            auto result = bytes.read_int64();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 4);
        }

        {
            auto result = bytes.read_int64();
            REQUIRE(result.has_value());
            REQUIRE(result.value() == 8);
        }
    }
}
