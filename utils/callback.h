//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_CALLBACK_H
#define DPI_TEST_CALLBACK_H

#include <cstring>
#include <cstdio>
#include <sys/un.h>

#include "defs.h"
#include "apis.h"
#include "jansson.h"
#include "utils/debug.h"

__thread int THREAD_ID;
__thread char THREAD_NAME[32];

class callback {
private:
    pthread_mutex_t g_debug_lock;
    struct timeval g_now;
    int g_ctrl_fd;
    struct sockaddr_un g_client_addr;
    int debug_ts(FILE *logfp);
public:
    int debug(bool print_ts, const char *fmt, va_list args);
    int ctrl_send_json (json_t *root);
    int ctrl_send_binary (void *buf, int len);
};

class dpi_callback_pcap: private callback{
public:
    int send_packet(io_ctx_t *ctx, uint8_t *data, int len);
    int threat_log (DPMsgThreatLog *log);
    int traffic_log (DPMsgSession *log);
    int connect_report (DPMsgSession *log, int count_session, int count_violate);
};

class dpi_callback_dp: private callback{
public:
    int send_packet(io_ctx_t *ctx, uint8_t *data, int len);
    int threat_log (DPMsgThreatLog *log);
    int traffic_log (DPMsgSession *log);
    int connect_report (DPMsgSession *log, int count_session, int count_violate);
};

#endif //DPI_TEST_CALLBACK_H
