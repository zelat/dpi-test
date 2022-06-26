//
// Created by tanchao on 2022/6/23.
//

#ifndef DPI_TEST_BASE_H
#define DPI_TEST_BASE_H

#include <inttypes.h>

//#ifndef likely
# define likely(x)        __builtin_expect(!!(x), 1)
//#endif
//#ifndef unlikely
# define unlikely(x)        __builtin_expect(!!(x), 0)
//#endif

#endif //DPI_TEST_BASE_H
