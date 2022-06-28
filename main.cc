#include <iostream>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <vector>
#include <sys/resource.h>
#include <getopt.h>
#include <iomanip>
#include <hs.h>

#include "base/Clock.h"
#include "base/dpi_adapter.h"
#include "base/dpi_hs_db.h"
#include "base/dpi_hs.h"
#include "utils/pcap.h"
#include "apis.h"
#include "utils/debug.h"
#include "utils/callback.h"

char *g_in_iface;
io_config_t g_config;
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

static int  test_dpi_hyperscan(int argc, char **argv){
    //hyeprscan测试
    const char * filename = argv[optind];
    const char * pcapFile = argv[optind + 1];

    hs_database_t *db_block, *db_streaming;
    dpi_db_from_file(filename, &db_streaming, &db_block);

    dpi_hs dpiHS(db_streaming, db_block);
    if (!dpiHS.dpi_read_streams(pcapFile)) {
        cerr << "Unable to read packets from PCAP file. Exiting." << endl;
        exit(-1);
    }
    dpiHS.dpi_display_stats();
    Clock clock;

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

    dpi_free_db(db_block);
    dpi_free_db(db_streaming);

    return 0;
}

int main(int argc, char **argv) {
    int arg = 0;
    while (arg != -1) {
        arg = getopt(argc, argv, "hcd:i:j:n:p:s");
        switch (arg) {
        case -1:
            break;
        case 'i':
            g_in_iface = strdup(optarg);
            g_config.promisc = true;
            break;
        case 'd':
            if (strcasecmp(optarg, "none") == 0) {
                g_debug_levels = 0;
            } else if (optarg[0] == '-') {
                g_debug_levels &= ~debug_name2level(optarg + 1);
            } else {
                g_debug_levels |= debug_name2level(optarg);
            }
                break;
        default:
            exit(-2);
        }
    }

    setlinebuf(stdout);

    g_callback.debug = debug_stdout;
//    g_callback.send_packet = dp_send_packet;

    cout << "g_debug_levels = " << g_debug_levels << endl;
    int ret = net_run(g_in_iface);
    cout << "ret = " << ret << endl;
    return ret;
//    //初始化线程互斥锁
//    pthread_mutex_init(&g_debug_lock, NULL);
//    rcu_map_init(&g_ep_map, 1, offsetof(io_mac_t, node), dp_ep_match, dp_ep_hash);
//    //Initalize subnet4 & subnet6 RCU LIST
//    CDS_LIST_HEAD(g_subnet4_list);
//    CDS_LIST_HEAD(g_subnet6_list);
//
//    init_dummy_ep(&g_config.dummy_ep);
//    g_config.dummy_mac.ep = &g_config.dummy_ep;
//
}

