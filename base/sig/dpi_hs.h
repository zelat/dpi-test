//
// Created by tanchao on 2022/6/22.
//

#ifndef DPI_TEST_DPI_HEADER_H
#define DPI_TEST_DPI_HEADER_H

#include <hs.h>
#include "utils/bits.h"
#include "dpi_sig.h"
#include "dpi_search.h"

typedef struct dpi_hs_summary_ {
    uint32_t db_count;       // number of databases
    uint32_t db_bytes;       // total bytes compiled
    uint32_t scratch_size;   // size of scratch space
} dpi_hs_summary_t;

typedef struct dpi_sig_assoc_ {
    dpi_sig_t *sig;
    uint16_t dlptbl_idx;
    uint8_t dpa_mask;
} dpi_sig_assoc_t;

typedef struct dpi_hyperscan_pattern_ {
    char *pattern;
    uint32_t pattern_len;
    uint32_t pattern_idx; /* actual pattern id */
    uint32_t hs_flags;
    dpi_sig_assoc_t hs_sa;
} dpi_hyperscan_pattern_t;

typedef struct dpi_hyperscan_pm_ {
    hs_database_t *db;
    dpi_hyperscan_pattern_t *hs_patterns;
    uint32_t hs_patterns_num; // number of elements
    uint32_t hs_patterns_cap; // allocated capacity
} dpi_hyperscan_pm_t;

typedef struct dpi_detector_ {
    uint32_t pat_count, dpi_act_count;//, eng_count, non_hidden_pat_count;
    dpi_sig_detect_tree_t *tree;
    struct cds_list_head dlpSigList;
    hs_scratch_t *dlp_hs_mpse_build_scratch;
    hs_scratch_t *dlp_hs_mpse_scan_scratch;
    hs_scratch_t *dlp_hs_pcre_build_scratch;
    hs_scratch_t *dlp_hs_pcre_scan_scratch;
    dpi_hs_summary_t dlp_pcre_hs_summary;
    dpi_hs_summary_t dlp_hs_summary;
    uint16_t dlp_ref_cnt;
    uint16_t dlp_ver;
    //int def_action;
    int dlp_apply_dir;
} dpi_detector_t;

#endif //DPI_TEST_DPI_HEADER_H
