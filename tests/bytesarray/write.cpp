#include <catch2/catch_test_macros.hpp>

#include <mkbase/byteio/byteio.hpp>

TEST_CASE("BytesArray write operations", "[bytesarray]") {
    SECTION("Write bytes") {
        auto bytes = monokuma::byteio::BytesArray({
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        });

        {
            auto write_result = bytes.write_byte('H');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[0] == 'H');
        }

        {
            auto write_result = bytes.write_byte('e');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[1] == 'e');
        }

        {
            auto write_result = bytes.write_byte('l');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[2] == 'l');
        }

        {
            auto write_result = bytes.write_byte('l');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[3] == 'l');
        }

        {
            auto write_result = bytes.write_byte('o');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[4] == 'o');
        }

        {
            auto write_result = bytes.write_byte(' ');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[5] == ' ');
        }

        {
            auto write_result = bytes.write_byte('W');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[6] == 'W');
        }

        {
            auto write_result = bytes.write_byte('o');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[7] == 'o');
        }

        {
            auto write_result = bytes.write_byte('r');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[8] == 'r');
        }

        {
            auto write_result = bytes.write_byte('l');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[9] == 'l');
        }

        {
            auto write_result = bytes.write_byte('d');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[10] == 'd');
        }

        {
            auto write_result = bytes.write_byte('!');
            REQUIRE(!write_result.has_value());
            REQUIRE(bytes.get_bytes()[11] == '!');
        }
    }
}