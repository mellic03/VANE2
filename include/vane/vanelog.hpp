#pragma once
#include <cstddef>
#include <format>

namespace vane
{
    enum class LogType: int
    {
        INFO, WARN, ERROR, FATAL
    };

    void vnlog(vane::LogType type, const char *title, const char *fmt, ...);

    // namespace vanelog
    // {
    //     namespace detail
    //     {
    //         void write(vane::LogType type, const char *msg);
    //     }
    // }
}

#define VLOG_INFO(...) \
    vane::vnlog(vane::LogType::INFO, __PRETTY_FUNCTION__, std::format(__VA_ARGS__).c_str())

#define VLOG_WARN(...) \
    vane::vnlog(vane::LogType::WARN, __PRETTY_FUNCTION__, std::format(__VA_ARGS__).c_str())

#define VLOG_ERROR(...) \
    vane::vnlog(vane::LogType::ERROR, __PRETTY_FUNCTION__, std::format(__VA_ARGS__).c_str())

#define VLOG_FATAL(...) \
    vane::vnlog(vane::LogType::FATAL, __PRETTY_FUNCTION__, std::format(__VA_ARGS__).c_str())

