//
// Created by tanchao on 2022/6/22.
//

#include "utils/rcu_map.h"
#include "base.h"

//初始化一个无锁的 RCU 保护的可调整大小的哈希表
rcu_map_t *rcu_map_init(rcu_map_t *m, uint32_t buckets, int node_offset,
                        cds_lfht_match_fct match_func, rcu_map_hash_fct hash_func)
{
    //创建一个指向hashtable本身的指针
    struct cds_lfht *ht_map;
    ht_map = cds_lfht_new(buckets, buckets, 0, CDS_LFHT_AUTO_RESIZE | CDS_LFHT_ACCOUNTING, nullptr);
    if (ht_map == nullptr) {
        return nullptr;
    }
    m->map = ht_map;
    m->match = match_func;
    m->hash = hash_func;
    m->offset = node_offset;
    return m;
}

//销毁该哈希表
int rcu_map_destroy(rcu_map_t *m)
{
    return cds_lfht_destroy(m->map, nullptr);
}

void rcu_map_add(rcu_map_t *m, void *data, const void *key)
{
    uint32_t hash = m->hash(key);

    cds_lfht_add(m->map, hash, (struct cds_lfht_node *)data);
}

void *rcu_map_add_replace(rcu_map_t *m, void *data, const void *key)
{
    uint32_t hash = m->hash(key);
    struct cds_lfht_node *node;

    node = cds_lfht_add_replace(m->map, hash, m->match, key, (struct cds_lfht_node *)data + m->offset);
    if (node == NULL) {
        return NULL;
    } else {
        return (struct cds_lfht_node *)node - m->offset;
    }
}

void *rcu_map_lookup(rcu_map_t *m, const void *key)
{
    struct cds_lfht_iter iter;
    struct cds_lfht_node *node;
    uint32_t hash = m->hash(key);

    cds_lfht_lookup(m->map, hash, m->match, key, &iter);
    node = cds_lfht_iter_get_node(&iter);
    if (node == nullptr) {
        return nullptr;
    }

    return (cds_lfht_node *)node - m->offset;
}

void rcu_map_for_each(rcu_map_t *m, rcu_map_for_each_fct each_func, void *args)
{
    struct cds_lfht_iter iter;
    struct cds_lfht_node *node;

    cds_lfht_for_each(m->map, &iter, node) {
        if (unlikely(each_func(node, args))) {
            break;
        }
    }
}

int rcu_map_del(rcu_map_t *m, void *data)
{
    return cds_lfht_del(m->map, (struct cds_lfht_node *)data + m->offset);
}


