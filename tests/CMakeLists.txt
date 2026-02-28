include("FetchContent")

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(mkbase_tests
        "${CMAKE_CURRENT_LIST_DIR}/bytestream.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/lazybytestream.cpp"
)

target_link_libraries(mkbase_tests
        PRIVATE Catch2::Catch2WithMain

        PRIVATE mkbase
)

list(APPEND CATCH_TEST_TARGETS mkbase_tests)
add_test(
        NAME mkbase_tests
        COMMAND mkbase_tests --reporter junit --out mkbase_tests_results.xml
)