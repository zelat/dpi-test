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

# Utility rule file for ragel_control_verbs.

# Include any custom commands dependencies for this target.
include CMakeFiles/ragel_control_verbs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ragel_control_verbs.dir/progress.make

CMakeFiles/ragel_control_verbs: src/parser/control_verbs.cpp

src/parser/control_verbs.cpp: src/parser/control_verbs.rl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating src/parser/control_verbs.cpp"
	/opt/cmake-3.20.0-linux-x86_64/bin/cmake -E make_directory /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser
	/usr/bin/ragel /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl -o /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.cpp

ragel_control_verbs: CMakeFiles/ragel_control_verbs
ragel_control_verbs: src/parser/control_verbs.cpp
ragel_control_verbs: CMakeFiles/ragel_control_verbs.dir/build.make
.PHONY : ragel_control_verbs

# Rule to build all files generated by this target.
CMakeFiles/ragel_control_verbs.dir/build: ragel_control_verbs
.PHONY : CMakeFiles/ragel_control_verbs.dir/build

CMakeFiles/ragel_control_verbs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ragel_control_verbs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ragel_control_verbs.dir/clean

CMakeFiles/ragel_control_verbs.dir/depend:
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles/ragel_control_verbs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ragel_control_verbs.dir/depend
