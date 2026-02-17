#include "vanelog.hpp"
#include "ansi.hpp"

#include <cstdarg>
#include <cstdio>

using namespace vane;

static void *vl_outfile_ = nullptr;
static void vl_printf(const char *fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    std::vfprintf((std::FILE*)vl_outfile_, fmt, vlist);
    va_end(vlist);
}


void vanelog::detail::write(vane::LogType type, const char *msg)
{
    const char *severity = "should_not_happen";
    const char *color = ANSI::RESET;

    switch (type)
    {
        using enum vane::LogType;

        case INFO:
            severity = "info";
            color = ANSI::Reg::GRN;
            break;
        case WARN:
            severity = "warn";
            color = ANSI::Bld::YEL;
            break;
        case ERROR:
            severity = "error";
            color = ANSI::BldHi::RED;
            break;
        case FATAL:
            severity = "fatal";
            color = ANSI::BldHi::RED;
            break;
        default:
            break;
    }

    vl_printf("%s[%s]%s   %s", color, severity, ANSI::RESET, msg);

    // if ((Logger::flags & log_flag::PRINT_LAZY) == false)
    // {
    //     Logger::print();
    //     std::cout << std::flush;
    // }
}
