# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.20.0-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.20.0-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0

# Utility rule file for ragel_ExpressionParser.

# Include any custom commands dependencies for this target.
include util/CMakeFiles/ragel_ExpressionParser.dir/compiler_depend.make

# Include the progress variables for this target.
include util/CMakeFiles/ragel_ExpressionParser.dir/progress.make

util/CMakeFiles/ragel_ExpressionParser: util/ExpressionParser.cpp

util/ExpressionParser.cpp: util/ExpressionParser.rl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ExpressionParser.cpp"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /opt/cmake-3.20.0-linux-x86_64/bin/cmake -E make_directory /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/ragel /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ExpressionParser.rl -o /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util//ExpressionParser.cpp

ragel_ExpressionParser: util/CMakeFiles/ragel_ExpressionParser
ragel_ExpressionParser: util/ExpressionParser.cpp
ragel_ExpressionParser: util/CMakeFiles/ragel_ExpressionParser.dir/build.make
.PHONY : ragel_ExpressionParser

# Rule to build all files generated by this target.
util/CMakeFiles/ragel_ExpressionParser.dir/build: ragel_ExpressionParser
.PHONY : util/CMakeFiles/ragel_ExpressionParser.dir/build

util/CMakeFiles/ragel_ExpressionParser.dir/clean:
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && $(CMAKE_COMMAND) -P CMakeFiles/ragel_ExpressionParser.dir/cmake_clean.cmake
.PHONY : util/CMakeFiles/ragel_ExpressionParser.dir/clean

util/CMakeFiles/ragel_ExpressionParser.dir/depend:
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/CMakeFiles/ragel_ExpressionParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : util/CMakeFiles/ragel_ExpressionParser.dir/depend
