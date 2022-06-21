# Install script for directory: /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELWITHDEBINFO")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/libhs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hs" TYPE FILE FILES
    "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/hs.h"
    "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/hs_common.h"
    "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/hs_compile.h"
    "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/hs_runtime.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/lib/libhs_runtime.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/lib/libhs.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/cmake_install.cmake")
  include("/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/doc/dev-reference/cmake_install.cmake")
  include("/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/unit/cmake_install.cmake")
  include("/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/tools/cmake_install.cmake")
  include("/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
