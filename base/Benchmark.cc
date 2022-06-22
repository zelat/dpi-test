//
// Created by Administrator on 2022/6/20.
//

#include "Benchmark.h"

using std::cerr;
using std::vector;
using std::string;
using std::unordered_map;
using std::endl;
using std::cout;

Benchmark::Benchmark(const hs_database_t *block)
        :db_block(block), scratch(nullptr),matchCount(0) {
    hs_error_t err = hs_alloc_scratch(db_block, &scratch);
    if (err != HS_SUCCESS){
        cerr << "ERROR: could not allocate scratch space. Exiting." << endl;
        exit(-1);
    }
}

Benchmark::~Benchmark() {
    hs_free_scratch(scratch);
}


//辅助函数，用于定位给定以太网帧中负载的第一个字节的偏移量。偏移量进入数据包，有效载荷的长度在参数@a偏移量和@a长度中返回。
bool Benchmark::payloadOffset(const unsigned char *pkt_data, unsigned int *offset,
                          unsigned int *length) {
    const ip *iph = (const ip *)(pkt_data + sizeof(ether_header));
    const tcphdr *th = nullptr;

    // Ignore packets that aren't IPv4
    if (iph->ip_v != 4) {
        return false;
    }

    // Ignore fragmented packets.
    if (iph->ip_off & htons(IP_MF|IP_OFFMASK)) {
        return false;
    }

    // IP header length, and transport header length.
    unsigned int ihlen = iph->ip_hl * 4;
    unsigned int thlen = 0;

    switch (iph->ip_p) {
        case IPPROTO_TCP:
            th = (const tcphdr *)((const char *)iph + ihlen);
            thlen = th->th_off * 4;
            break;
        case IPPROTO_UDP:
            thlen = sizeof(udphdr);
            break;
        default:
            return false;
    }

    *offset = sizeof(ether_header) + ihlen + thlen;
    *length = sizeof(ether_header) + ntohs(iph->ip_len) - *offset;

    return *length != 0;
}

bool Benchmark::readStreams(const char *pcapFile) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcapHandle = pcap_open_offline(pcapFile, errbuf);
    if (pcapHandle == nullptr) {
        cerr << "ERROR: Unable to open pcap file \"" << pcapFile
             << "\": " << errbuf << endl;
        return false;
    }

    struct pcap_pkthdr pktHeader;
    const unsigned char * pktData;
    while ((pktData = pcap_next(pcapHandle, &pktHeader)) != nullptr) {
        unsigned int offset = 0, length = 0;
        if (!payloadOffset(pktData, &offset, &length)){
            continue;
        }
        const struct ip *iphdr = (const struct ip *)(pktData
                                                     + sizeof(struct ether_header));
        const char *payload = (const char *)pktData + offset;

        size_t id = stream_map.insert(std::make_pair(FiveTuple(iphdr),
                                                     stream_map.size())).first->second;
        packets.push_back(string(payload, length));
        stream_ids.push_back(id);
        pcap_close(pcapHandle);

        return !packets.empty();
    }
}

// Return the number of bytes scanned
size_t Benchmark::bytes() const {
    size_t sum = 0;
    for (const auto &packet : packets) {
        sum += packet.size();
    }
    return sum;
}

// Return the number of matches found.
size_t Benchmark::matches() const {
    return matchCount;
}

// Clear the number of matches found.
void Benchmark::clearMatches() {
    matchCount = 0;
}

// Scan each packet (in the ordering given in the PCAP file) through
// Hyperscan using the block-mode interface.
void Benchmark::scanBlock() {
    for (size_t i = 0; i != packets.size(); ++i) {
        const std::string &pkt = packets[i];
        hs_error_t err = hs_scan(db_block, pkt.c_str(), pkt.length(), 0,
                                 scratch, onMatch, &matchCount);
        if (err != HS_SUCCESS) {
            cerr << "ERROR: Unable to scan packet. Exiting." << endl;
            exit(-1);
        }
    }
}

void Benchmark::displayStats(){
    size_t numPackets = packets.size();
    size_t numStreams = stream_map.size();
    size_t numBytes = bytes();
    hs_error_t err;

    cout << numPackets << " packets in " << numStreams
         << " streams, totalling " << numBytes << " bytes." << endl;
    cout << "Average packet length: " << numBytes / numPackets << " bytes."
         << endl;
    cout << "Average stream length: " << numBytes / numStreams << " bytes."
         << endl;
    cout << endl;

    size_t dbBlock_size = 0;
    err = hs_database_size(db_block, &dbBlock_size);
    if (err == HS_SUCCESS) {
        cout << "Block mode Hyperscan database size        : "
             << dbBlock_size << " bytes." << endl;
    } else {
        cout << "Error getting block mode Hyperscan database size"
             << endl;
    }
}