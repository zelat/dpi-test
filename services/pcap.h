//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_PCAP_H
#define DPI_TEST_PCAP_H

#include <cstring>
#include "apis.h"

extern int g_running;
extern int g_dp_threads;

static void dp_signal_exit(int num);
int count_cpu(void);
int net_run(const char *in_iface);

int dp_ep_match(struct cds_lfht_node *ht_node, const void *key);
uint32_t dp_ep_hash(const void *key);
int ep_app_match(struct cds_lfht_node *ht_node, const void *key);
uint32_t ep_app_hash(const void *key);
void init_dummy_ep(io_ep_t *ep);
struct timeval tv_diff(struct timeval s, struct timeval e);

#endif //DPI_TEST_PCAP_H
