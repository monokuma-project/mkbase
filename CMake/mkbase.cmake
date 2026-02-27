option(MKBASE_ERROR_AUTOTELL "Automatic log error when its constructed" OFF)

# Now library has only headers
if (BUILD_SHARED_LIBS)
    add_library(mkbase INTERFACE)
    target_compile_definitions(mkbase PRIVATE MKBASE_DLL)
else ()
    add_library(mkbase INTERFACE)
endif ()

target_include_directories(mkbase
        INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../src"
)

if (MKBASE_ERROR_AUTOTELL)
    target_compile_definitions(mkbase INTERFACE ERROR_AUTO_TELLING)
endif ()

target_compile_definitions(mkbase INTERFACE MKBASE_COMPILATION)