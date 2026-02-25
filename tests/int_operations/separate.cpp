#include <catch2/catch_test_macros.hpp>

#include <array>

#include <mkbase/byteio/int_operations.hpp>

TEST_CASE("Int operations separate", "[int_operations]") {
    SECTION("Separate int32 to bytes") {
        {
            auto bytes = monokuma::byteio::separate_i32_to_bytes(2);
            REQUIRE(bytes[0] == 0b00000010);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
        }

        {
            auto bytes = monokuma::byteio::separate_i32_to_bytes(4);
            REQUIRE(bytes[0] == 0b00000100);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
        }

        {
            auto bytes = monokuma::byteio::separate_i32_to_bytes(8);
            REQUIRE(bytes[0] == 0b00001000);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
        }
    }

    SECTION("Separate int64 to bytes") {
        {
            auto bytes = monokuma::byteio::separate_i64_to_bytes(2);
            REQUIRE(bytes[0] == 0b00000010);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
            REQUIRE(bytes[4] == 0b00000000);
            REQUIRE(bytes[5] == 0b00000000);
            REQUIRE(bytes[6] == 0b00000000);
            REQUIRE(bytes[7] == 0b00000000);
        }

        {
            auto bytes = monokuma::byteio::separate_i64_to_bytes(4);
            REQUIRE(bytes[0] == 0b00000100);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
            REQUIRE(bytes[4] == 0b00000000);
            REQUIRE(bytes[5] == 0b00000000);
            REQUIRE(bytes[6] == 0b00000000);
            REQUIRE(bytes[7] == 0b00000000);
        }

        {
            auto bytes = monokuma::byteio::separate_i64_to_bytes(8);
            REQUIRE(bytes[0] == 0b00001000);
            REQUIRE(bytes[1] == 0b00000000);
            REQUIRE(bytes[2] == 0b00000000);
            REQUIRE(bytes[3] == 0b00000000);
            REQUIRE(bytes[4] == 0b00000000);
            REQUIRE(bytes[5] == 0b00000000);
            REQUIRE(bytes[6] == 0b00000000);
            REQUIRE(bytes[7] == 0b00000000);
        }
    }
}