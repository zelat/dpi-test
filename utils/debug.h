//
// Created by tanchao on 2022/6/24.
//

#ifndef DPI_TEST_DEBUG_H
#define DPI_TEST_DEBUG_H

#define DBG_ENUM_INIT    0
#define DBG_ENUM_ERROR   1
#define DBG_ENUM_CTRL    2
#define DBG_ENUM_PACKET  3
#define DBG_ENUM_SESSION 4
#define DBG_ENUM_TIMER   5
#define DBG_ENUM_TCP     6
#define DBG_ENUM_PARSER  7
#define DBG_ENUM_LOG     8
#define DBG_ENUM_DDOS    9
#define DBG_ENUM_POLICY  10
#define DBG_ENUM_DETECT  11

#define DBG_INIT    (1 << DBG_ENUM_INIT)    // 0000
#define DBG_ERROR   (1 << DBG_ENUM_ERROR)   // 0010
#define DBG_CTRL    (1 << DBG_ENUM_CTRL)    // 0100
#define DBG_PACKET  (1 << DBG_ENUM_PACKET)  // 1000
#define DBG_SESSION (1 << DBG_ENUM_SESSION) // 1 0000
#define DBG_TIMER   (1 << DBG_ENUM_TIMER)   // 10 0000
#define DBG_TCP     (1 << DBG_ENUM_TCP)     // 100 0000
#define DBG_PARSER  (1 << DBG_ENUM_PARSER)  // 1000 0000
#define DBG_LOG     (1 << DBG_ENUM_LOG)     // 1 0000 0000
#define DBG_DDOS    (1 << DBG_ENUM_DDOS)    // 10 0000 0000
#define DBG_POLICY  (1 << DBG_ENUM_POLICY)  // 100 0000 0000
#define DBG_DETECT  (1 << DBG_ENUM_DETECT)  // 1000 0000 0000

#define DBG_DEFAULT (DBG_INIT|DBG_ERROR)

extern uint32_t g_debug_levels;

#define DEBUG_LOG_NO_FILTER(format, args...) \
debug_log(true, "%s: " format, __FUNCTION__, ##args)

#define IF_DEBUG(level) \
if (unlikely(g_debug_levels & (level)))

#define DEBUG_LEVEL(level, format, args...) \
IF_DEBUG(level) { debug_log_no_filter(true, "%s: " format, __FUNCTION__,  ##args); }
#define DEBUG_ERROR(level, format, args...) \
IF_DEBUG(level | DBG_ERROR) { debug_log_no_filter(true, "%s: " format, __FUNCTION__,  ##args); }
#define DEBUG_INIT(format, args...) \
IF_DEBUG(DBG_INIT) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }
#define DEBUG_CTRL(format, args...) \
IF_DEBUG(DBG_CTRL) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }
#define DEBUG_PACKET(format, args...) \
IF_DEBUG(DBG_PACKET) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }
#define DEBUG_LOGGER(format, args...) \
IF_DEBUG(DBG_LOG) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }
#define DEBUG_TIMER(format, args...) \
IF_DEBUG(DBG_TIMER) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }

#define DEBUG_POLICY(format, args...) \
IF_DEBUG(DBG_POLICY) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }

#define DEBUG_DLP(format, args...) \
IF_DEBUG(DBG_DETECT) { debug_log_no_filter(true, "%s: " format, __FUNCTION__, ##args); }

#define DEBUG_FUNC_ENTRY(level) \
IF_DEBUG(level) { debug_log_no_filter(true, "%s: enter\n", __FUNCTION__); }

#endif //DPI_TEST_DEBUG_H
