#include <catch2/catch_test_macros.hpp>

#include <mkbase/byteio/byteio.hpp>

TEST_CASE("BytesArray read operations", "[bytesarray]") {
    SECTION("read bytes") {
        auto bytes = monokuma::byteio::BytesArray({
            'H', 'e', 'l', 'l', 'o',
            ' ',
            'W', 'o', 'r', 'l', 'd', '!',
        });

        for (std::size_t i = 0; i < bytes.get_bytes().size(); ++i) {
            auto byte = bytes.read_byte();
            REQUIRE(byte.has_value());
            REQUIRE(byte.value() == bytes.get_bytes()[i]);
        }
    }
}