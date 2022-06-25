//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_DEBUG_H
#define DPI_TEST_DEBUG_H

#define DBG_ENUM_CTRL    2

#define DBG_CTRL    (1 << DBG_ENUM_CTRL)

#define DEBUG_ERROR(level, format, args...) \
        IF_DEBUG(level | DBG_ERROR) { debug_log_no_filter(true, "%s: " format, __FUNCTION__,  ##args); }
#define DEBUG_CTRL(format, args...) \
        IF_DEBUG(DBG_CTRL) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }

#endif //DPI_TEST_DEBUG_H
