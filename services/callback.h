//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_CALLBACK_H
#define DPI_TEST_CALLBACK_H

#include <cstring>
#include <cstdio>
#include <sys/un.h>
#include <fcntl.h>

#include "config.h"
#include "defs.h"
#include "apis.h"
#include "jansson.h"
#include "utils/debug.h"

extern __thread int THREAD_ID;
extern __thread char THREAD_NAME[32];

extern pthread_mutex_t g_debug_lock;
extern struct timeval g_now;
extern int g_ctrl_fd;
extern struct sockaddr_un g_client_addr;

int debug_ts(FILE *logfp);

int debug_stdout(bool print_ts, const char *fmt, va_list args);

int debug_file(bool print_ts, const char *fmt, va_list args);

int ctrl_send_json(json_t *root);

int ctrl_send_binary(void *buf, int len);

int send_packet(io_ctx_t *ctx, uint8_t *data, int len);

int threat_log(DPMsgThreatLog *log);

int traffic_log(DPMsgSession *log);

int connect_report(DPMsgSession *log, int count_session, int count_violate);


#endif //DPI_TEST_CALLBACK_H
