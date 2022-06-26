//
// Created by tanchao on 2022/6/26.
//

#include <cstdarg>
#include <apis.h>

extern io_callback_t g_callback;

void debug_log_no_filter(bool print_ts, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    g_callback.debug(print_ts, fmt, args);
    va_end(args);
}