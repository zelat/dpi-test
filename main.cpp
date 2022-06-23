#include <iostream>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <vector>
#include <sys/resource.h>
#include "base/Clock.h"
#include "base/dpi_adapter.h"
#include "apis.h"

#include <hs.h>
#include <getopt.h>
#include <pcap.h>
#include <iomanip>
#include <base/dpi_hs.h>

io_config_t g_config;
pthread_mutex_t g_debug_lock;
rcu_map_t g_ep_map;


using std::ifstream;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::cout;

static int test_calloc(){
    int * p = (int*) calloc(10, sizeof(int));

    if (p == NULL) {
        std::cout << "%s\n" << strerror(errno);
    } else {
        int i;
        for (i = 0; i < 10; i++)
        {
            printf("%d ", *(p + i));//0 0 0 0 0 0 0 0 0 0
        }
    }
    free(p);
    p = NULL;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


static int alloc_mem(){
    //设置资源限制
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM64_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
    memset(&g_config, 0 , sizeof(g_config));
    return 0;
}

static void test_dpi_adapter(){
    //获取网络设备
    dpi_adapter dpi;
    dpi.dpi_select_adapter();
    dpi.dpi_open_adapter();
}

static void test_dpi_hs(const char * filename,  hs_database_t *db_block){
    dpi_hs dpiHS(db_block);
    dpiHS.dpi_db_from_file(filename, &db_block);

    dpiHS.dpi_free_db();
}

int main(int argc, char **argv) {
    //设置线程互斥锁
//    pthread_mutex_init(&g_debug_lock, NULL);
//    rcu_map_init(&g_ep_map, 1, offsetof(io_mac_t, node), dp_ep_match, dp_ep_hash);



    //hyeprscan测试
    const char * filename = argv[optind];
    const char * pcapFile = argv[optind + 1];

    hs_database_t *db_block;
    dpi_hs dpiHS(db_block);
    dpiHS.dpi_db_from_file(filename, &db_block);
    if (!dpiHS.dpi_read_streams(pcapFile)) {
        cerr << "Unable to read packets from PCAP file. Exiting." << endl;
        exit(-1);
    }
    Clock clock;
    dpiHS.dpi_display_stats();
    // Scan all our packets in block mode.
    dpiHS.clearMatches();
    clock.start();
    dpiHS.dpi_scan_block();
    clock.stop();
    double secsScanBlock = clock.seconds();
    // Collect data from block mode scans.
    size_t bytes = dpiHS.bytes();
    double tputBlockScanning = (bytes * 8) / secsScanBlock;
    size_t matchesBlock = dpiHS.matches();
    double matchRateBlock = matchesBlock / ((bytes) / 1024.0); // matches per kilobyte
    cout << endl << "Block mode:" << endl << endl;
    cout << "  Total matches: " << matchesBlock << endl;
    cout << std::fixed << std::setprecision(4);
    cout << "  Match rate:    " << matchRateBlock << " matches/kilobyte" << endl;
    cout << std::fixed << std::setprecision(2);
    cout << "  Throughput:    "
         << tputBlockScanning/1000000 << " megabits/sec" << endl;
    cout << endl;
    if (bytes < (2*1024*1024)) {
        cout << endl << "WARNING: Input PCAP file is less than 2MB in size." << endl
             << "This test may have been too short to calculate accurate results." << endl;
    }

    dpiHS.dpi_free_db();

    return 0;
}
