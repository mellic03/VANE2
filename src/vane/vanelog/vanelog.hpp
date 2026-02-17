#pragma once
#include <cstddef>

namespace vane
{
    enum class LogType: int
    {
        INFO, WARN, ERROR, FATAL
    };

    namespace vanelog
    {
        namespace detail
        {
            void write(vane::LogType type, const char *msg);
        }
    }
}

#define VLOG_INFO(...) \
    vanelog::detail::write(vane::LogType::INFO, __PRETTY_FUNCTION__, std::format(__VA_ARGS__))

#define VLOG_WARN(...) \
    vanelog::detail::write(vane::LogType::WARN, __PRETTY_FUNCTION__, std::format(__VA_ARGS__))

#define VLOG_ERROR(...) \
    vanelog::detail::write(vane::LogType::ERROR, __PRETTY_FUNCTION__, std::format(__VA_ARGS__))

#define VLOG_FATAL(...) \
    vanelog::detail::write(vane::LogType::FATAL, __PRETTY_FUNCTION__, std::format(__VA_ARGS__))

