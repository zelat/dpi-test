//
// Created by tanchao on 2022/6/23.
//

#ifndef DPI_TEST_APIS_H
#define DPI_TEST_APIS_H

#include <netinet/in.h>
#include <net/ethernet.h>
#include <jansson.h>
#include "defs.h"
#include "utils/rcu_map.h"

#define MAX_THREAD_NAME_LEN 32
extern __thread int THREAD_ID;
extern __thread char THREAD_NAME[MAX_THREAD_NAME_LEN];

#define IFACE_NAME_LEN 32
#define STATS_SLOTS 60
#define STATS_INTERVAL 5 // in second
#define STRUCT_OF(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct io_metry_ {
    uint64_t session;
    uint64_t packet;
    uint64_t byte;
    uint32_t sess_ring[STATS_SLOTS];
    uint32_t pkt_ring[STATS_SLOTS];
    uint32_t byte_ring[STATS_SLOTS];
    uint32_t cur_session;
} io_metry_t;

typedef union io_ip_ {
    struct in6_addr ip6;
    uint32_t ip4;
} io_ip_t;

typedef struct io_pip_ {
    uint32_t ip;
} io_pip_t;

typedef struct io_stats_ {
    uint32_t cur_slot;
    io_metry_t in, out;
    // io_metry_t app_in[DPI_PROTO_MAX];
    // io_metry_t app_out[DPI_PROTO_MAX];
} io_stats_t;

typedef struct io_internal_pip_ {
    int count;
    io_pip_t list[0];
} io_internal_pip_t;

typedef struct io_ep_ {
    char iface[IFACE_NAME_LEN];
    struct io_mac_ *mac;    // Original MAC
    struct io_mac_ *ucmac;
    struct io_mac_ *bcmac;
    struct ether_addr pmac; // proxymesh's Original MAC
    io_internal_pip_t *pips; // proxymesh's parent IPs

    uint32_t COPY_START;

    io_stats_t stats;

    rcu_map_t app_map;
    uint32_t app_updated;
    uint16_t app_ports;

    bool tap;
    uint8_t cassandra_svr: 1,
            kafka_svr:     1,
            couchbase_svr: 1,
            couchbase_clt: 1,
            zookeeper_svr: 1,
            zookeeper_clt: 1;
    void *policy_hdl;
    uint16_t policy_ver;

    rcu_map_t dlp_cfg_map;
    rcu_map_t waf_cfg_map;
    rcu_map_t dlp_rid_map;
    rcu_map_t waf_rid_map;
    void *dlp_detector;
    uint16_t dlp_detect_ver;
    bool dlp_inside;
} io_ep_t;

typedef struct io_mac_ {
    struct cds_lfht_node node;
    struct ether_addr mac;
    io_ep_t *ep;
    uint8_t broadcast:1,
            unicast:  1;
} io_mac_t;

typedef struct io_app_ {
    struct cds_lfht_node node;
    uint16_t port;
    uint16_t proto;
    uint16_t server;
    uint16_t application;
#define SERVER_VER_SIZE 32
    char version[SERVER_VER_SIZE];
    bool listen;
    uint8_t ip_proto;
#define APP_SRC_CTRL  1
#define APP_SRC_DP    2
    uint8_t src;
} io_app_t;

typedef struct io_ctx_ {
    void *dp_ctx;
    uint32_t tick;
    uint32_t stats_slot;
    struct ether_addr ep_mac;
    bool large_frame;
    bool tap;
    bool tc;
    bool nfq;
} io_ctx_t;

typedef struct io_callback_ {
    int (*debug) (bool print_ts, const char *fmt, va_list args);
    int (*send_packet) (io_ctx_t *ctx, uint8_t *data, int len);
    int (*send_ctrl_json) (json_t *root);
    int (*send_ctrl_binary) (void *buf, int len);
    int (*threat_log) (DPMsgThreatLog *log);
    int (*traffic_log) (DPMsgSession *log);
    int (*connect_report) (DPMsgSession *log, int count_session, int count_violate);
} io_callback_t;

typedef struct dpi_config_ {
    bool enable_cksum;
    bool promisc;

    io_mac_t dummy_mac;
    io_ep_t dummy_ep;
} io_config_t;


#endif //DPI_TEST_APIS_H
