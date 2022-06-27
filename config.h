//
// Created by tanchao on 2022/6/27.
//

#ifndef DPI_TEST_CONFIG_H
#define DPI_TEST_CONFIG_H

#include <ctime>

static uint32_t g_seconds;
static time_t g_start_time;

#define MAX_DP_THREADS 4


extern time_t get_current_time()
{
    return (g_start_time + g_seconds);
}
#endif //DPI_TEST_CONFIG_H
