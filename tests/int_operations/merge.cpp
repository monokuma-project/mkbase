#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/byteio/int_operations.hpp>

TEST_CASE("Int operations: merge", "[int_operations]") {
    SECTION("Merge bytes to int32") {
        {
            std::array<monokuma::byteio::byte, 4> bytes = {
                0b00000010,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i32(bytes) == 2);
        }

        {
            std::array<monokuma::byteio::byte, 4> bytes = {
                0b00000100,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i32(bytes) == 4);
        }

        {
            std::array<monokuma::byteio::byte, 4> bytes = {
                0b00001000,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i32(bytes) == 8);
        }
    }

    SECTION("Merge bytes to int64") {
        {
            std::array<monokuma::byteio::byte, 8> bytes = {
                0b00000010,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i64(bytes) == 2);
        }

        {
            std::array<monokuma::byteio::byte, 8> bytes = {
                0b00000100,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i64(bytes) == 4);
        }

        {
            std::array<monokuma::byteio::byte, 8> bytes = {
                0b00001000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
            };

            REQUIRE(monokuma::byteio::merge_bytes_to_i64(bytes) == 8);
        }
    }
}