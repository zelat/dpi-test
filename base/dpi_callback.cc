//
// Created by tanchao on 2022/6/24.
//

#include "dpi_callback.h"
#include "config.h"

int dpi_callback::debug_ts(FILE *logfp) {
    struct timeval now;
    struct tm *tm;

    if (g_now.tv_sec == 0) {
        time_t t = get_current_time();
        tm = localtime((const time_t *)&t);
    } else {
        now = g_now;
        tm = localtime(&now.tv_sec);
    }

    return fprintf(logfp, "%04d-%02d-%02dT%02d:%02d:%02d|DEBU|%s|",
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec, THREAD_NAME);
}

int dpi_callback::debug(bool print_ts, const char *fmt, va_list args) {
    int len = 0;

    pthread_mutex_lock(&g_debug_lock);
    if (print_ts) {
        len = debug_ts(stdout);
    }
    len += vprintf(fmt, args);
    pthread_mutex_unlock(&g_debug_lock);

    return len;
}

int dpi_callback::ctrl_send_json(json_t *root) {
    if (root == NULL) {
        DEBUG_ERROR(DBG_CTRL, "Fail to create json object.\n");
        return -1;
    }

    char *data = json_dumps(root, 0);
    if (data == NULL) {
        DEBUG_ERROR(DBG_CTRL, "Fail to dump json object.\n");
        json_decref(root);
        // 'root' steal all its children's reference. As it is released, return 0 so the caller
        // won't call free() again.
        return 0;
    }

    socklen_t addr_len = sizeof(struct sockaddr_un);
    int sent = sendto(g_ctrl_fd, data, strlen(data), 0,
                      (struct sockaddr *)&g_client_addr, addr_len);
    DEBUG_CTRL("%s\n", data);

    free(data);
    json_decref(root);

    return sent;
}

int dpi_callback::ctrl_send_binary(void *buf, int len) {
    return 0;
}

