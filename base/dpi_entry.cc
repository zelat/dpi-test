//
// Created by Administrator on 2022/6/29.
//

#include "dpi_entry.h"
#include "config.h"
#include "dpi_module.h"

dpi_entry::dpi_entry(io_callback_t *cb, io_config_t *cfg){
    g_io_callback = cb;
    g_io_config = cfg;

//    dpi_packet_setup();
//    dpi_parser_setup();
//    dpi_dlp_init();
    std::cout << "testing" << std::endl;
}

dpi_entry::~dpi_entry() {

}

