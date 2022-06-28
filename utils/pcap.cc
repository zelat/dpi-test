//
// Created by tanchao on 2022/6/24.
//
#include <iostream>
#include <csignal>
#include "pcap.h"
#include "config.h"
#include "debug.h"
#include "timer_queue.h"
#include "ctrl.h"

int g_running; // dp是否running
int g_dp_threads = 0 ; //初始化dp线程数

uint32_t sdbm_hash(register const uint8_t *a, register int len) {
    register uint32_t hash = 0;

    while (len > 0) {
        hash = *a + (hash << 6) + (hash << 16) - hash;
        a++;
        len--;
    }

    return hash;
}

int dp_ep_match(struct cds_lfht_node *ht_node, const void *key) {
    io_mac_t *ht_mac = STRUCT_OF(ht_node, io_mac_t, node);
    const u_int8_t *mac = (uint8_t *) key;

    return memcmp(mac, &ht_mac->mac, sizeof(ht_mac->mac)) == 0 ? 1 : 0;
}

uint32_t dp_ep_hash(const void *key) {
    const u_int8_t *k = (uint8_t *) key;
    return sdbm_hash(k, ETH_ALEN);
}

int ep_app_match(struct cds_lfht_node *ht_node, const void *key) {
    io_app_t *app = STRUCT_OF(ht_node, io_app_t, node);
    const io_app_t *k = (io_app_t *) key;
    return app->port == k->port && app->ip_proto == k->ip_proto;
}

uint32_t ep_app_hash(const void *key) {
    const io_app_t *app = (io_app_t *) key;
    return app->port ^ app->ip_proto;
}

void init_dummy_ep(io_ep_t *ep) {
    rcu_map_init(&ep->app_map, 4, offsetof(io_app_t, node), ep_app_match, ep_app_hash);
    ep->tap = true;
}

struct timeval tv_diff(struct timeval s, struct timeval e) {
    struct timeval d;
    if (e.tv_usec < s.tv_usec) {
        d.tv_sec = e.tv_sec - s.tv_sec - 1;
        d.tv_usec = 1000000 + e.tv_usec - s.tv_usec;
    } else {
        d.tv_sec = e.tv_sec - s.tv_sec;
        d.tv_usec = e.tv_usec - s.tv_usec;
    }
    return d;
}

static void dp_signal_exit(int num) {
    g_running = false;
}

// 计算cpu数目
int count_cpu(void) {
    FILE *fp;
    int n = 0, ret;

    fp = popen("nproc", "r");
    if (fp == NULL) {
        return 1;
    }

    ret = fscanf(fp, "%d", &n);
    fclose(fp);

    return ret > 0 ? n : 1;
}

// 控制dp线程
int net_run(const char *in_iface) {
    pthread_t timer_thr;
    pthread_t bld_dlp_thr;
    pthread_t dp_thr[MAX_DP_THREADS];
    int i, timer_thr_id, bld_dlp_thr_id, thr_id[MAX_DP_THREADS];

    DEBUG_FUNC_ENTRY(DBG_INIT);
    g_running = true;
    //发送给本程序的终止请求信号
    signal(SIGTERM, dp_signal_exit);
    //中断信号，如 ctrl-C，通常由用户生成
    signal(SIGINT, dp_signal_exit);
    signal(SIGQUIT, dp_signal_exit);

    // Calculate number of dp threads
    if (g_dp_threads == 0) {
        g_dp_threads = count_cpu();
        std::cout << "count_cpu = " << g_dp_threads << std::endl;
    }
    if (g_dp_threads > MAX_DP_THREADS) {
        g_dp_threads = MAX_DP_THREADS;
    }

    //获取线程数，一个cpu分配一个线程
    std::cout << "g_dp_threads = " << g_dp_threads << std::endl;

    ctrl cl;
    cl.dp_ctrl_init_thread_data();
    return 0;
}