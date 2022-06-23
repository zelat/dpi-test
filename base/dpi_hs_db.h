//
// Created by Administrator on 2022/6/23.
//

#ifndef DPI_TEST_DPI_HS_DB_H
#define DPI_TEST_DPI_HS_DB_H

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
#include <hs.h>

using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::unordered_map;


void dpi_db_from_file(const char *filename,hs_database_t **db_streaming, hs_database_t **db_block);
void dpi_free_db(hs_database_t *block);
unsigned parseFlags(const string &flagsStr);
int parseFile(const char * filename, vector<string> &patterns, vector<unsigned> &flags, vector<unsigned> &ids);
hs_database_t * dpi_build_db(const vector<const char *> &expressions, const vector<unsigned> flags, const vector<unsigned> ids, unsigned int mode);

#endif //DPI_TEST_DPI_HS_DB_H
