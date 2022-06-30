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

include(cmake/Modules/hyperscan-5.4.0.cmake)
include(cmake/Modules/pcap-1.9.0.cmake)
include(cmake/Modules/userspace-rcu-0.13.1.cmake)
include(cmake/Modules/jansson-2.14.cmake)
include(cmake/Modules/libnetfilter_queue-1.0.5.cmake)
include(cmake/Modules/pcre2-10.40.cmake)
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
        "${CMAKE_SOURCE_DIR}/utils/debug.cc"
        "${CMAKE_SOURCE_DIR}/utils/timer_queue.cc"
        "${CMAKE_SOURCE_DIR}/utils/timer_wheel.cc"
        "${CMAKE_SOURCE_DIR}/utils/asm.cc"
        "${CMAKE_SOURCE_DIR}/utils/asn1.cc"
        "${CMAKE_SOURCE_DIR}/utils/bitmap.cc"
        "${CMAKE_SOURCE_DIR}/utils/helper.cc"
        "${CMAKE_SOURCE_DIR}/utils/tree.cc"
        )
target_link_libraries(utils urcu urcu-cds) #urcu-cds rt stdc++ m mnl netfilter_queue

add_library(sig "")
target_sources(sig
        PRIVATE
        "${CMAKE_SOURCE_DIR}/base/sig/dpi_hs_search.cc"
        "${CMAKE_SOURCE_DIR}/base/sig/dpi_search.cc"
        "${CMAKE_SOURCE_DIR}/base/sig/dpi_sig.cc"
        )
target_link_libraries(sig utils)
target_link_libraries(sig pcre2)

add_library(parsers "")
target_sources(parsers
        PRIVATE
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_cassandra.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_couchbase.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_dhcp.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_dns.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_echo.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_grpc.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_http.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_kafka.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_mongodb.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_mysql.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_ntp.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_postgresql.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_redis.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_spark.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_sqlinjection.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_ssh.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_ssl.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_tds.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_tftp.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_tns.cc"
        "${CMAKE_SOURCE_DIR}/base/parsers/dpi_zookeeper.cc"
        )
target_link_libraries(parsers utils)

add_library(services "")
target_sources(services
        PRIVATE
        "${CMAKE_SOURCE_DIR}/services/ctrl.cc"
        "${CMAKE_SOURCE_DIR}/services/callback.cc"
        "${CMAKE_SOURCE_DIR}/services/pcap.cc"
        )
target_link_libraries(services utils)


add_library(base "")
target_sources(base
        PRIVATE
        "${CMAKE_SOURCE_DIR}/base/dpi_adapter.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_hs.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_hs_db.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_entry.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_debug.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_packet.cc"
        "${CMAKE_SOURCE_DIR}/base/dpi_session.cc"
        )
target_link_libraries(base hs pcap jansson)
target_link_libraries(base utils parsers sig)

add_executable(dpi_test main.cc)
target_link_libraries(dpi_test base utils netfilter_queue)
target_link_libraries(services)
#target_link_libraries(dpi_test hs pcap network utils)