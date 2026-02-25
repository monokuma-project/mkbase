include("FetchContent")

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(mkbase_tests
        "bytesarray/read.cpp"
        "bytesarray/write.cpp"

        "bytestream/read.cpp"
        "bytestream/write.cpp"

        "int_operations/merge.cpp"
        "int_operations/separate.cpp"
)

target_link_libraries(mkbase_tests
        PRIVATE Catch2::Catch2WithMain

        PRIVATE mkbase
)

include("Catch")
catch_discover_tests(mkbase_tests)