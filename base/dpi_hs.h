//
// Created by Administrator on 2022/6/21.
//

#ifndef DPI_TEST_DPI_HS_H
#define DPI_TEST_DPI_HS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <hs.h>


using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;



class dpi_hs {
private:
    hs_database_t *db_block;
    hs_scratch_t *scratch;
    hs_database_t * dpi_build_db(const vector<const char *> &expressions, const vector<unsigned> flags, const vector<unsigned> ids, unsigned int mode);
public:
    dpi_hs(const hs_database_t *block);
    ~dpi_hs();
    void dpi_db_from_file(const char *filename, hs_database_t **db_block);
    void dpi_free_db();
    unsigned parseFlags(const string &flagsStr);
    int parseFile(const char * filename, vector<string> &patterns, vector<unsigned> &flags, vector<unsigned> &ids);
};
#endif //DPI_TEST_DPI_HS_H
