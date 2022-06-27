//
// Created by Administrator on 2022/6/27.
//

#include "ctrl.h"
#include "utils/pcap.h"

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