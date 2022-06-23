//
// Created by tanchao on 2022/6/22.
//

#include "rcu_map.h"

rcu_map::rcu_map() {
    ht_map = cds_lfht_new(buckets, buckets, 0, CDS_LFHT_AUTO_RESIZE | CDS_LFHT_ACCOUNTING, NULL);

}

rcu_map::~rcu_map() {
}