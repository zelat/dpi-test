//
// Created by tanchao on 2022/6/29.
//

#ifndef DPI_TEST_DPI_HS_SEARCH_H
#define DPI_TEST_DPI_HS_SEARCH_H

#include "hs.h"
#include "dpi_hs.h"
#include "utils/debug.h"

#define INITIAL_PATTERN_ARRAY_ALLOC_SIZE 10

class dpi_hs_search {
private:
    dpi_detector_t *detector;
    void ActivateScratch(hs_scratch_t **build_scratch, hs_scratch_t **scan_scratch);
    dpi_hyperscan_pm_t *dpi_hs_create();
public:
    dpi_hs_search(void *dlpdetector);
    ~dpi_hs_search();
    void * dpi_dlp_hs_search_create();
    void dpi_dlp_hs_search_add_dlprule();
    void dpi_dlp_hs_search_compile();
    void dpi_dlp_hs_search_detect();
    void HyperscanActivate();
    void HyperscanActivateMpse();
    void HyperscanActivatePcre();
};


#endif //DPI_TEST_DPI_HS_SEARCH_H
