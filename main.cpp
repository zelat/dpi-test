#include <iostream>
#include <string.h>
#include <errno.h>
#include <vector>
#include "base/Benchmark.h"
#include "base/Clock.h"

#include <hs.h>
#include <getopt.h>
#include <pcap.h>
#include <iomanip>


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

static unsigned parseFlags(const string &flagsStr) {
    unsigned flags = 0;
    for (const auto &c : flagsStr) {
        switch (c) {
            case 'i':
                flags |= HS_FLAG_CASELESS; break;
            case 'm':
                flags |= HS_FLAG_MULTILINE; break;
            case 's':
                flags |= HS_FLAG_DOTALL; break;
            case 'H':
                flags |= HS_FLAG_SINGLEMATCH; break;
            case 'V':
                flags |= HS_FLAG_ALLOWEMPTY; break;
            case '8':
                flags |= HS_FLAG_UTF8; break;
            case 'W':
                flags |= HS_FLAG_UCP; break;
            case '\r': // stray carriage-return
                break;
            default:
                cerr << "Unsupported flag \'" << c << "\'" << endl;
                exit(-1);
        }
    }
    return flags;
}

static int parseFile(const char * filename, vector<string> &patterns,
                      vector<unsigned> &flags, vector<unsigned> &ids){
    ifstream inFile(filename);
    if (!inFile.good()){
        cerr << "ERROR: Can't open pattern file \"" << filename << "\"" << endl;
        exit(-1);
    }
    for (unsigned i = 1; !inFile.eof(); ++i) {
        string line;
        getline(inFile, line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        size_t colonIdx = line.find_first_of(':');
        if (colonIdx == string::npos) {
            cerr << "ERROR: Could not parse line " << i << endl;
            exit(-1);
        }
        //获取pattern ID
        unsigned id = std::stoi(line.substr(0, colonIdx).c_str());

        const string expr(line.substr(colonIdx+1));
        size_t flagsStart = expr.find_last_of('/');
        if (flagsStart == string::npos) {
            cerr << "ERROR: no trailing '/' char" << endl;
            exit(-1);
        }
        string pcre(expr.substr(1, flagsStart - 1));
        string flagsStr(expr.substr(flagsStart + 1, expr.size() - flagsStart));
        unsigned flag = parseFlags(flagsStr);

        patterns.push_back(pcre);
        flags.push_back(flag);
        ids.push_back(id);
    }
    return 0;
}

static hs_database_t *buildDatabase(const vector<const char *> &expressions,
                                    const vector<unsigned> flags,
                                    const vector<unsigned> ids,
                                    unsigned int mode){
    hs_database_t *db;
    hs_compile_error_t *compileErr;
    hs_error_t err;

    err = hs_compile_multi(expressions.data(), flags.data(), ids.data(), expressions.size(),
                           mode, nullptr, &db, &compileErr);
    if (err != HS_SUCCESS){
        if (compileErr->expression < 0) {
            // The error does not refer to a particular expression.
            cerr << "ERROR: " << compileErr->message << endl;
        } else {
            cerr << "ERROR: Pattern '" << expressions[compileErr->expression]
                 << "' failed compilation with error: " << compileErr->message
                 << endl;
        }
        hs_free_compile_error(compileErr);
        exit(-1);
    }

    return db;
}

static void databaseFromFile(const char *filename, hs_database_t **db_block){
    vector<string> patterns;
    vector<unsigned> flags;
    vector<unsigned> ids;

    parseFile(filename, patterns, flags, ids);

    //解析pattern
    for (int i = 0; i < patterns.size(); i++) {
        cout << patterns[i] << endl;
    }
    //解析flags
    for (int j = 0; j < flags.size(); j++) {
        cout << flags[j] << endl;
    }
    //解析ids
    for (int k = 0; k < flags.size(); k++) {
        cout << ids[k] << endl;
    }

    vector<const char*> cstrPatterns;
    for (const auto &pattern : patterns) {
        cstrPatterns.push_back(pattern.c_str());
    }

    cout << "Compiling Hyperscan databases with " << patterns.size()
         << " patterns." << endl;

    *db_block = buildDatabase(cstrPatterns, flags, ids, HS_MODE_BLOCK);
}

int main(int argc, char **argv) {
    const char * filename = argv[optind];
    const char * pcapFile = argv[optind + 1];

    hs_database_t *db_block;
    databaseFromFile(filename, &db_block);
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

    hs_free_database(db_block);
    return 0;
}
