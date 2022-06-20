//
// Created by Administrator on 2022/6/20.
//

#ifndef DPI_TEST_BENCHMARK_H
#define DPI_TEST_BENCHMARK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
// We use the BSD primitives throughout as they exist on both BSD and Linux.
#define __FAVOR_BSD
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>


#include <pcap.h>
#include <hs.h>

using std::cerr;
using std::vector;
using std::string;
using std::unordered_map;
using std::endl;


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


class Benchmark {
private:
    vector<string> packets;
    vector<size_t> stream_ids;
    unordered_map<FiveTuple, size_t, FiveTupleHash> stream_map;
    const hs_database_t *db_block;
    hs_scratch_t *scratch;
    size_t matchCount;
public:
    Benchmark(const hs_database_t *block);
    ~Benchmark();
    bool payloadOffset(const unsigned char *pkt_data, unsigned int *offset, unsigned int *length);
    bool readStreams(const char *pcapFile);
    size_t bytes() const;
    size_t matches() const;
    void clearMatches();
    void scanBlock();
    void displayStats();
};


#endif //DPI_TEST_BENCHMARK_H
