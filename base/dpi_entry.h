//
// Created by Administrator on 2022/6/29.
//

#ifndef DPI_TEST_DPI_ENTRY_H
#define DPI_TEST_DPI_ENTRY_H

#include <iostream>
#include "apis.h"


class dpi_entry {
private:
    io_callback_t *g_io_callback;
    io_config_t *g_io_config;
public:
    dpi_entry(io_callback_t *cb, io_config_t *cfg);
    ~dpi_entry();
};


#endif //DPI_TEST_DPI_ENTRY_H
