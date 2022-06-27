//
// Created by tanchao on 2022/6/27.
//

#ifndef DPI_TEST_CTRL_H
#define DPI_TEST_CTRL_H


#include <csignal>
#include <cstdint>
#include "config.h"
#include "utils/rcu_map.h"
#include "defs.h"


class ctrl {
private:
    pthread_cond_t g_ctrl_req_cond;
    pthread_mutex_t g_ctrl_req_lock;
    pthread_cond_t g_dlp_ctrl_req_cond;
    pthread_mutex_t g_dlp_ctrl_req_lock;
public:
    void dp_ctrl_init_thread_data(void);
};


#endif //DPI_TEST_CTRL_H
