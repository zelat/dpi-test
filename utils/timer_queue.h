//
// Created by Administrator on 2022/6/27.
//

#ifndef DPI_TEST_TIMER_QUEUE_H
#define DPI_TEST_TIMER_QUEUE_H

#include <cstdint>
#include "urcu/list.h"

typedef struct timer_node_ {
    struct cds_list_head link;
    uint32_t last;
} timer_node_t;

typedef void (*timer_queue_remove_fct)(timer_node_t *n);

typedef struct timer_queue_ {
    struct cds_list_head head;
    uint32_t count;
    uint32_t timeout;
} timer_queue_t;

class timer_queue {
private:
    timer_queue_t *q;
public:
    timer_queue(timer_queue_t *q, uint32_t timeout);
    void timer_queue_touch(timer_node_t *n, uint32_t now);
    void timer_queue_remove(timer_node_t *n);
    void timer_queue_append(timer_node_t *n, uint32_t now);
    uint32_t timer_queue_trim(uint32_t now, timer_queue_remove_fct remove);
    uint32_t timer_queue_purge(timer_queue_remove_fct remove);
};


#endif //DPI_TEST_TIMER_QUEUE_H
