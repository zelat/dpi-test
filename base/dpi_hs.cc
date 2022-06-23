//
// Created by tanchao on 2022/6/21.
//

#include "dpi_hs.h"

//分配scratch space
dpi_hs::dpi_hs(const hs_database_t *streaming, const hs_database_t *block)
        : db_streaming(streaming), db_block(block), scratch(nullptr), matchCount(0){
    cout << "START" << endl;
    hs_error_t err = hs_alloc_scratch(db_streaming, &scratch);
    cout << "End" << endl;
    if (err != HS_SUCCESS) {
        cerr << "ERROR: could not allocate scratch space. Exiting." << endl;
        exit(-1);
    }

    err = hs_alloc_scratch(db_block, &scratch);
    if (err != HS_SUCCESS){
        cerr << "ERROR: could not allocate scratch space. Exiting." << endl;
        exit(-1);
    }
}

//释放scratch space
dpi_hs::~dpi_hs() {
    hs_free_scratch(scratch);
}

// Scan each packet (in the ordering given in the PCAP file) through
// Hyperscan using the block-mode interface.
void dpi_hs::dpi_scan_block() {
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

bool dpi_hs::dpi_read_streams(const char *pcapFile) {
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
        if (!dpi_payload_offset(pktData, &offset, &length)){
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

// Open a Hyperscan stream for each stream in stream_ids
void dpi_hs::dpi_open_streams() {
    streams.resize(stream_map.size());
    for (auto &stream : streams) {
        hs_error_t err = hs_open_stream(db_streaming, 0, &stream);
        if (err != HS_SUCCESS) {
            cerr << "ERROR: Unable to open stream. Exiting." << endl;
            exit(-1);
        }
    }
}

// Close all open Hyperscan streams (potentially generating any
// end-anchored matches)
void dpi_hs::dpi_close_streams() {
    for (auto &stream : streams) {
        hs_error_t err = hs_close_stream(stream, scratch, onMatch,
                                         &matchCount);
        if (err != HS_SUCCESS) {
            cerr << "ERROR: Unable to close stream. Exiting." << endl;
            exit(-1);
        }
    }
}

// Scan each packet (in the ordering given in the PCAP file) through
// Hyperscan using the streaming interface.
void dpi_hs::dpi_scan_streams() {
    for (size_t i = 0; i != packets.size(); ++i) {
        const std::string &pkt = packets[i];
        hs_error_t err = hs_scan_stream(streams[stream_ids[i]],
                                        pkt.c_str(), pkt.length(), 0,
                                        scratch, onMatch, &matchCount);
        if (err != HS_SUCCESS) {
            cerr << "ERROR: Unable to scan packet. Exiting." << endl;
            exit(-1);
        }
    }
}

//辅助函数，用于定位给定以太网帧中负载的第一个字节的偏移量。偏移量进入数据包，有效载荷的长度在参数@a偏移量和@a长度中返回。
bool dpi_hs::dpi_payload_offset(const unsigned char *pkt_data, unsigned int *offset,
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

// Return the number of bytes scanned
size_t dpi_hs::bytes() const {
    size_t sum = 0;
    for (const auto &packet : packets) {
        sum += packet.size();
    }
    return sum;
}

// Return the number of matches found.
size_t dpi_hs::matches() const {
    return matchCount;
}

// Clear the number of matches found.
void dpi_hs::clearMatches() {
    matchCount = 0;
}

// Display some information about the compiled database and scanned data.
void dpi_hs::dpi_display_stats() {
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

    size_t dbStream_size = 0;
    err = hs_database_size(db_streaming, &dbStream_size);
    if (err == HS_SUCCESS) {
        cout << "Streaming mode Hyperscan database size    : "
             << dbStream_size << " bytes." << endl;
    } else {
        cout << "Error getting streaming mode Hyperscan database size"
             << endl;
    }

    size_t dbBlock_size = 0;
    err = hs_database_size(db_block, &dbBlock_size);
    if (err == HS_SUCCESS) {
        cout << "Block mode Hyperscan database size        : "
             << dbBlock_size << " bytes." << endl;
    } else {
        cout << "Error getting block mode Hyperscan database size"
             << endl;
    }

    size_t stream_size = 0;
    err = hs_stream_size(db_streaming, &stream_size);
    if (err == HS_SUCCESS) {
        cout << "Streaming mode Hyperscan stream state size: "
             << stream_size << " bytes (per stream)." << endl;
    } else {
        cout << "Error getting stream state size" << endl;
    }
}