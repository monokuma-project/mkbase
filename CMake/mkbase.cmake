option(MKBASE_ERROR_AUTOTELL "Automatic log error when its constructed" OFF)

if (BUILD_SHARED_LIBS)
    add_library(mkbase SHARED)
    target_compile_definitions(mkbase PRIVATE MKBASE_DLL)
else ()
    add_library(mkbase STATIC)
endif ()

target_include_directories(mkbase
        PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../src"
)

if (MKBASE_ERROR_AUTOTELL)
    target_compile_definitions(mkbase PRIVATE ERROR_AUTO_TELLING)
endif ()

target_compile_definitions(mkbase PRIVATE MKBASE_COMPILATION)

file(GLOB MKBASE_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/../src/mkbase/byteio/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../src/mkbase/byteio/bytesarray/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../src/mkbase/byteio/bytestream/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../src/mkbase/byteio/filestream/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../src/mkbase/logging/*.cpp"
)

target_sources(mkbase PRIVATE ${MKBASE_SOURCES})