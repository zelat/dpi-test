//
// Created by Administrator on 2022/6/27.
//

#include "ctrl.h"
#include "utils/debug.h"

int ctrl::conn4_match(struct cds_lfht_node *ht_node, const void *key)
{
    conn_node_t *cnode = STRUCT_OF(ht_node, conn_node_t, node);
    DPMsgConnect *conn = &cnode->conn;
    const conn4_key_t *ckey = (conn4_key_t *)key;

    return (conn->PolicyId == ckey->pol_id &&
            ip4_get(conn->ClientIP) == ckey->client &&
            ip4_get(conn->ServerIP) == ckey->server &&
            !!FLAGS_TEST(conn->Flags, DPCONN_FLAG_INGRESS) == ckey->ingress &&
            conn->Application == ckey->application &&
            conn->ServerPort == ckey->port && conn->IPProto == ckey->ipproto) ? 1 : 0;
}

uint32_t ctrl::conn4_hash(const void *key)
{
    const conn4_key_t *ckey = (conn4_key_t *)key;

    return sdbm_hash((uint8_t *)&ckey->client, 4) +
           sdbm_hash((uint8_t *)&ckey->server, 4) + ckey->port + ckey->ingress + ckey->pol_id;
}

ctrl::ctrl() {}

//初始化dp线程结构
void ctrl::dp_ctrl_init_thread_data(void)
{
    int thr_id, i;

    for (thr_id = 0; thr_id < g_dp_threads; thr_id ++) {
        dp_thread_data_t *th_data = &g_dp_thread_data[thr_id];

        // Log ring
        th_data->log_reader = MAX_LOG_ENTRIES - 1;
        for (i = 0; i < MAX_LOG_ENTRIES; i ++) {
            DPMsgHdr *hdr = (DPMsgHdr *)th_data->log_ring[i];
            hdr->Kind = DP_KIND_THREAT_LOG;
            hdr->Length = htons(LOG_ENTRY_SIZE);
        }

        // Connection map
        rcu_map_init(&th_data->conn4_map[0], 128, offsetof(conn_node_t, node),
                     conn4_match, conn4_hash);
        rcu_map_init(&th_data->conn4_map[1], 128, offsetof(conn_node_t, node),
                     conn4_match, conn4_hash);
        th_data->conn4_map_cnt[0] = 0;
        th_data->conn4_map_cnt[1] = 0;
        dp_rate_limiter_reset(&th_data->conn4_rl, CONNECT_RL_DUR, CONNECT_RL_CNT);
        uatomic_set(&th_data->conn4_map_cur, 0);
    }
}

void ctrl::dp_rate_limiter_reset(dp_rate_limter_t *rl, uint16_t dur, uint16_t dur_cnt_limit)
{
    memset(rl, 0, sizeof(dp_rate_limter_t));
    rl->dur = dur;
    rl->dur_cnt_limit = dur_cnt_limit;
    rl->start = get_current_time();
}
