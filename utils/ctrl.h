//
// Created by tanchao on 2022/6/27.
//

#ifndef DPI_TEST_CTRL_H
#define DPI_TEST_CTRL_H

#include <iostream>
#include <csignal>
#include <cstdint>
#include "config.h"
#include "utils/pcap.h"
#include "base.h"
#include "defs.h"

typedef struct conn_node_ {
    struct cds_lfht_node node;
    DPMsgConnect conn;
} conn_node_t;

typedef struct conn4_key_ {
    uint32_t pol_id;
    uint32_t client, server;
    uint16_t port;
    uint16_t application;
    uint8_t ipproto;
    bool ingress;
} conn4_key_t;

static inline uint32_t ip4_get(uint8_t *ip)
{
    return *(uint32_t *)ip;
}

#define FLAGS_TEST(f, b)  (f & b)

class ctrl {
private:
    pthread_cond_t g_ctrl_req_cond;
    pthread_mutex_t g_ctrl_req_lock;
    pthread_cond_t g_dlp_ctrl_req_cond;
    pthread_mutex_t g_dlp_ctrl_req_lock;
    dp_thread_data_t g_dp_thread_data[MAX_DP_THREADS];

    static int conn4_match(struct cds_lfht_node *ht_node, const void *key);
    static uint32_t conn4_hash(const void *key);
public:
    ctrl();
    void dp_ctrl_init_thread_data(void);
    void dp_rate_limiter_reset(dp_rate_limter_t *rl, uint16_t dur, uint16_t dur_cnt_limit);
};


#endif //DPI_TEST_CTRL_H
