//
// Created by Administrator on 2022/6/22.
//

#ifndef DPI_TEST_RCU_MAP_H
#define DPI_TEST_RCU_MAP_H

#include "urcu.h"
#include "urcu/rculfhash.h"

typedef uint32_t (*rcu_map_hash_fct)(const void *key);

typedef struct rcu_map_ {
    struct cds_lfht *map;
    cds_lfht_match_fct match;
    rcu_map_hash_fct hash;
    int offset;
} rcu_map_t;

class rcu_map {
private:
    struct cds_lfht *ht_map;
    rcu_map_t *m;
    uint32_t buckets;
    int node_offset;
    cds_lfht_match_fct match_func;
    rcu_map_hash_fct hash_func;
public:
    rcu_map();
    ~rcu_map();
};


#endif //DPI_TEST_RCU_MAP_H
