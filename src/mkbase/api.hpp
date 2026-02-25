#pragma once

#ifdef _WIN32
    #ifdef MKBASE_DLL
        #ifdef MKBASE_COMPILATION
            #define MKBASE_API __declspec(dllexport)
        #else
            #define MKBASE_API __declspec(dllimport)
        #endif
    #else
        #define MKBASE_API
    #endif
#else
    #define MKBASE_API
#endif