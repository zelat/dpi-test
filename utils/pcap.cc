//
// Created by tanchao on 2022/6/24.
//

#include "pcap.h"

inline uint32_t sdbm_hash(register const uint8_t *a, register int len)
{
    register uint32_t hash = 0;

    while (len > 0) {
        hash = *a + (hash << 6) + (hash << 16) - hash;
        a ++; len --;
    }

    return hash;
}

int dp_ep_match(struct cds_lfht_node *ht_node, const void *key)
{
    io_mac_t *ht_mac = STRUCT_OF(ht_node, io_mac_t, node);
    const u_int8_t *mac = (uint8_t *)key;

    return memcmp(mac, &ht_mac->mac, sizeof(ht_mac->mac)) == 0 ? 1 : 0;
}

uint32_t dp_ep_hash(const void *key)
{
    const u_int8_t *k = (uint8_t *)key;
    return sdbm_hash(k, ETH_ALEN);
}

int ep_app_match(struct cds_lfht_node *ht_node, const void *key)
{
    io_app_t *app = STRUCT_OF(ht_node, io_app_t, node);
    const io_app_t *k = (io_app_t *)key;
    return app->port == k->port && app->ip_proto == k->ip_proto;
}

uint32_t ep_app_hash(const void *key)
{
    const io_app_t *app = (io_app_t *)key;
    return app->port ^ app->ip_proto;
}

void init_dummy_ep(io_ep_t *ep)
{
    rcu_map_init(&ep->app_map, 4, offsetof(io_app_t, node), ep_app_match, ep_app_hash);
    ep->tap = true;
}

struct timeval tv_diff(struct timeval s, struct timeval e)
{
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