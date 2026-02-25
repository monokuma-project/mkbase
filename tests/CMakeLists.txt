include("FetchContent")

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(mkbase_tests
        "${CMAKE_CURRENT_LIST_DIR}/bytesarray/read.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/bytesarray/write.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/bytestream/read.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/bytestream/write.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/int_operations/merge.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/int_operations/separate.cpp"
)

target_link_libraries(mkbase_tests
        PRIVATE Catch2::Catch2WithMain

        PRIVATE mkbase
)

include("Catch")
catch_discover_tests(mkbase_tests)