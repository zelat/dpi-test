//
// Created by Administrator on 2022/6/21.
//

#ifndef DPI_TEST_DPI_ADAPER_H
#define DPI_TEST_DPI_ADAPER_H

#include <iostream>
#include "pcap.h"

using std::cout;
using std::endl;

class dpi_adapter {
private:
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i = 0;
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    static void dpi_packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);
public:
    dpi_adapter();
    ~dpi_adapter();
    int dpi_open_adapter();
    int dpi_select_adapter();
};


#endif //DPI_TEST_DPI_ADAPER_H
