cmake_minimum_required(VERSION 3.20)
project("dpi_test" VERSION 1.0.0 LANGUAGES C CXX)

# This project use c99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# This project requires c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -s" )
#
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s" )

include(cmake/Modules/hyperscan-5.4.0.cmake)
include(cmake/Modules/pcap-1.9.0.cmake)
include(cmake/Modules/userspace-urcu-0.13.1.cmake)

#编译时候的选项
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wno-unused-result -Wno-unused-function -fstrict-aliasing -Wstrict-aliasing -g")

set(CMAKE_BUILD_TYPE "Release")
# PROJECT_SOURCE_DIR指的是工程顶层目录
include_directories(
        "${PROJECT_SOURCE_DIR}"
)

find_package (Threads)

add_library(utils "")
target_sources(utils
        PRIVATE
        "${CMAKE_SOURCE_DIR}/utils/rcu_map.cc"
        )
target_link_libraries(utils urcu urcu-cds) #urcu-cds rt stdc++ m mnl netfilter_queue


add_library(network "")
target_sources(network
        PRIVATE
        "${CMAKE_SOURCE_DIR}/base/Benchmark.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_adapter.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_hs.cc"
        )
target_link_libraries(network hs pcap)

add_executable(dpi_test main.cpp)
target_link_libraries(dpi_test hs pcap network utils)