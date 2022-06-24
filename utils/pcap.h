//
// Created by Administrator on 2022/6/24.
//

#ifndef DPI_TEST_PCAP_H
#define DPI_TEST_PCAP_H

#include "apis.h"

int ep_app_match(struct cds_lfht_node *ht_node, const void *key);
uint32_t ep_app_hash(const void *key);
void init_dummy_ep(io_ep_t *ep);

#endif //DPI_TEST_PCAP_H
