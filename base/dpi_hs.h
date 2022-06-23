//
// Created by tanchao on 2022/6/21.
//

#ifndef DPI_TEST_DPI_HS_H
#define DPI_TEST_DPI_HS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <vector>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <net/ethernet.h>

#include "pcap/pcap.h"
#include "hs.h"

using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::unordered_map;

struct FiveTuple {
    unsigned int protocol;
    unsigned int srcAddr;
    unsigned int srcPort;
    unsigned int dstAddr;
    unsigned int dstPort;

    // Construct a FiveTuple from a TCP or UDP packet.
    FiveTuple(const struct ip *iphdr) {
        // IP fields
        protocol = iphdr->ip_p;
        srcAddr = iphdr->ip_src.s_addr;
        dstAddr = iphdr->ip_dst.s_addr;

        // UDP/TCP ports
        const struct udphdr *uh =
                (const struct udphdr *)(((const char *)iphdr) + (iphdr->ip_hl * 4));
        srcPort = uh->uh_sport;
        dstPort = uh->uh_dport;
    }

    bool operator==(const FiveTuple &a) const {
        return protocol == a.protocol && srcAddr == a.srcAddr &&
               srcPort == a.srcPort && dstAddr == a.dstAddr &&
               dstPort == a.dstPort;
    }
};

struct FiveTupleHash {
    size_t operator()(const FiveTuple &x) const {
        return x.srcAddr ^ x.dstAddr ^ x.protocol ^ x.srcPort ^ x.dstPort;
    }
};

// Match event handler: called every time Hyperscan finds a match.
static int onMatch(unsigned int id, unsigned long long from, unsigned long long to,
                   unsigned int flags, void *ctx) {
    // Our context points to a size_t storing the match count
    size_t *matches = (size_t *)ctx;
    (*matches)++;
    return 0; // continue matching
}

class dpi_hs {
private:
    hs_database_t *db_block;
    hs_database_t *db_streaming;
    hs_scratch_t *scratch;
    // Packet data to be scanned.
    vector<string> packets;
    // The stream ID to which each packet belongs
    vector<size_t> stream_ids;
    // Map used to construct stream_ids
    unordered_map<FiveTuple, size_t, FiveTupleHash> stream_map;
    // Vector of Hyperscan stream state (used in streaming mode)
    vector<hs_stream_t *> streams;
    // Count of matches found during scanning
    size_t matchCount;
public:
    dpi_hs(const hs_database_t *block);
    ~dpi_hs();
    void dpi_db_from_file(const char *filename, hs_database_t **db_block);
    void dpi_free_db();
    unsigned parseFlags(const string &flagsStr);
    int parseFile(const char * filename, vector<string> &patterns, vector<unsigned> &flags, vector<unsigned> &ids);
    bool dpi_read_streams(const char *pcapFile);
    bool dpi_payload_offset(const unsigned char *pkt_data, unsigned int *offset,unsigned int *length);
    size_t bytes() const;
    size_t matches() const;
    void clearMatches();
    void dpi_open_streams();
    void dpi_close_streams();
    void dpi_scan_streams();
    void dpi_scan_block();
    void dpi_display_stats();
    hs_database_t * dpi_build_db(const vector<const char *> &expressions, const vector<unsigned> flags, const vector<unsigned> ids, unsigned int mode);
};
#endif //DPI_TEST_DPI_HS_H
