//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_DPI_CALLBACK_H
#define DPI_TEST_DPI_CALLBACK_H

#include <cstring>
#include <cstdio>
#include <sys/un.h>

#include "defs.h"
#include "apis.h"
#include "jansson.h"
#include "debug.h"

class dpi_callback {
private:
    pthread_mutex_t g_debug_lock;
    struct timeval g_now;
    int g_ctrl_fd;
    struct sockaddr_un g_client_addr;
    time_t get_current_time();
    int debug_ts(FILE *logfp);
public:
    int debug(bool print_ts, const char *fmt, va_list args);
    int send_ctrl_json (json_t *root);
    int send_ctrl_binary (void *buf, int len);
    virtual int send_packet(io_ctx_t *ctx, uint8_t *data, int len);
    virtual int threat_log (DPMsgThreatLog *log);
    virtual int traffic_log (DPMsgSession *log);
    virtual int connect_report (DPMsgSession *log, int count_session, int count_violate);
};

class dpi_callback_pcap: private dpi_callback{
public:
    int send_packet(io_ctx_t *ctx, uint8_t *data, int len);
    int threat_log (DPMsgThreatLog *log);
    int traffic_log (DPMsgSession *log);
    int connect_report (DPMsgSession *log, int count_session, int count_violate);
};

class dpi_callback_dp: private dpi_callback{
public:
    int send_packet(io_ctx_t *ctx, uint8_t *data, int len);
    int threat_log (DPMsgThreatLog *log);
    int traffic_log (DPMsgSession *log);
    int connect_report (DPMsgSession *log, int count_session, int count_violate);
};

#endif //DPI_TEST_DPI_CALLBACK_H
