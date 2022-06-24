//
// Created by Administrator on 2022/6/24.
//

#include "pcap.h"

int ep_app_match(struct cds_lfht_node *ht_node, const void *key)
{
    io_app_t *app = STRUCT_OF(ht_node, io_app_t, node);
    const io_app_t *k = key;
    return app->port == k->port && app->ip_proto == k->ip_proto;
}

uint32_t ep_app_hash(const void *key)
{
    const io_app_t *app = key;
    return app->port ^ app->ip_proto;
}

void init_dummy_ep(io_ep_t *ep)
{
    rcu_map_init(&ep->app_map, 4, offsetof(io_app_t, node), ep_app_match, ep_app_hash);
    ep->tap = true;
}