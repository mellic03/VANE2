#pragma once

#define VANE_DEBUG


#ifdef VANE_DEBUG
    namespace vane::detail
    {
        void vnassert(const char *file, int line, bool cond, const char *condstr, const char *msg);
    }

    #define VANE_ASSERT(Cond, Msg) vane::detail::vnassert(__FILE__, __LINE__, Cond, #Cond, Msg)
    // #define VANE_ASSERT(...) vane::detail::vnassert(cond, __FILE__, __LINE__, std::format(__VA_ARGS__).c_str())

#else
    #define VANE_ASSERT()

#endif
