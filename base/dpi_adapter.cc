//
// Created by tanchao on 2022/6/21.
//

#include "dpi_adapter.h"

dpi_adapter::dpi_adapter(){
    //获取设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        cout << "Error in pcap_findalldevs: " << errbuf << endl;
        exit(1);
    }
    //打印设备列表
    for (d = alldevs; d != NULL; d = d->next) {
        cout << ++i << "."<< d->name;
        if (d->description) {
            cout << "(" << d->description << ")" << endl;
        } else {
            cout << "(No description available)" << endl;
        }
    }

    if (i == 0) {
        printf("/nNo interfaces found! Make sure WinPcap is installed./n");
    }
}

int dpi_adapter::dpi_select_adapter(){
    printf("Enter the interface number (1-%d):", i);
    scanf("%d", &inum);
    if (inum < 1 || inum > 1){
        cout << "Interface number out of range" << endl;
        pcap_freealldevs(alldevs);
    }

}

dpi_adapter::~dpi_adapter() {
    pcap_freealldevs(alldevs);
}


int dpi_adapter::dpi_open_adapter(){
    for (d=alldevs, i = 0; i < inum - 1; d=d->next, i++);
    //device: Specifies a string that contains the name of the network device to open for packet capture, for example, en0.
    //snaplen: Specifies the maximum number of bytes to capture per packet.
    //promisc: Specifies that the device is to be put into promiscuous mode. A value of 1 (True) turns promiscuous mode on.
    //         If this parameter is 0 (False), the device will remain unchanged. In this case,
    //         if it has already been set to promiscuous mode (for some other reason), it will remain in this mode.
    //to_ms: Specifies the read timeout in milliseconds.
    //ebuf: Returns error text and is only set when the pcap_open_live subroutine fails.
    if ((adhandle= pcap_open_live(d->name, 65536, 1, 1000, errbuf)) == NULL){
        cout << "Unable to open the adapter." << d->name << " is not supported by libcap" << endl;
        pcap_freealldevs(alldevs);
        exit(-1);
    }

    //释放设备列表
    pcap_freealldevs(alldevs);
    pcap_loop(adhandle, 0, dpi_packet_handler, nullptr);
    pcap_close(adhandle);
}

void dpi_adapter::dpi_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *packet_data){
    struct tm * ltime;
    char timestr[16];
    time_t local_tv_sec;

    local_tv_sec = header -> ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

    //打印数据包的捕获时间与数据包的长度
//    printf("%s, %.6d len:%d", timestr, header->ts.tv_sec, header->len, "\n");
    cout << timestr << ":" << header->ts.tv_sec << ", len:" << header->len << endl;
}