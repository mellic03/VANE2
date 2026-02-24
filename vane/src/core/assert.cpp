#include "vane/assert.hpp"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>


void vane::detail::vnassert(const char *file, int line, bool cond, const char *condstr, const char *msg)
{
    if (cond == true)
    {
        return;
    }

    std::printf("-------- ASSERT FAIL --------\n");
    std::printf("Assert:  %s\n", condstr);
    std::printf("Message: %s\n", condstr);
    std::printf("Source:  %s:%s\n", file, line);
    std::abort();
}

