//
// Created by Administrator on 2022/6/22.
//

#ifndef DPI_TEST_RCU_MAP_H
#define DPI_TEST_RCU_MAP_H

#include "urcu.h"
#include "urcu/rculfhash.h"

class rcu_map {
private:
    struct cds_lfht *ht_map;
    rcu_map_t *m;
public:
    rcu_map();
    ~rcu_map();
};


#endif //DPI_TEST_RCU_MAP_H
