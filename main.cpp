#include <iostream>
#include <string.h>
#include <errno.h>
#include <vector>
#include "base/Benchmark.h"
#include "base/Clock.h"
#include "base/dpi_adapter.h"

#include <hs.h>
#include <getopt.h>
#include <pcap.h>
#include <iomanip>
#include <base/dpi_hs.h>


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

int main(int argc, char **argv) {
    //获取网络设备
//    dpi_adapter dpi;
//    dpi.dpi_select_adapter();
//    dpi.dpi_open_adapter();



    //hyeprscan测试
    const char * filename = argv[optind];
    const char * pcapFile = argv[optind + 1];

    hs_database_t *db_block;
    dpi_hs dpiHS(filename, &db_block);
    // Read our input PCAP file in
    Benchmark bench(db_block);
    cout << "PCAP input file: " << pcapFile << endl;
    if (!bench.readStreams(pcapFile)) {
        cerr << "Unable to read packets from PCAP file. Exiting." << endl;
        exit(-1);
    }
    Clock clock;
    bench.displayStats();
    // Scan all our packets in block mode.
    bench.clearMatches();
    clock.start();

    bench.scanBlock();
    clock.stop();

    double secsScanBlock = clock.seconds();

    // Collect data from block mode scans.
    size_t bytes = bench.bytes();
    double tputBlockScanning = (bytes * 8) / secsScanBlock;
    size_t matchesBlock = bench.matches();
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
    return 0;
}
