#pragma once

#define VANE_DEBUG

#ifdef VANE_DEBUG
    #include <cassert>
    #include <cstdio>

    #define STR_HELPER(x) #x
    #define STR(x) STR_HELPER(x)

    #define VANE_ASSERT(Cndtn, Mesge, ...) \
    do { \
        if (!(Cndtn)) { \
            fprintf(stderr, \
                "Assertion failed: (%s)\nFile: %s\nLine: %s\nMessage: " Mesge "\n", \
                #Cndtn, __FILE__, STR(__LINE__), ##__VA_ARGS__); \
            fflush(stderr); \
            exit(1); \
        } \
    } while (false)
#else
    #define VANE_ASSERT(Cndtn, Mesge, ...) do { } while (false)
#endif

