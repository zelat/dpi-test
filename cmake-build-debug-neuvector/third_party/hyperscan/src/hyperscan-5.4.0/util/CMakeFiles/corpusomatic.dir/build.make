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

# Include any dependencies generated for this target.
include util/CMakeFiles/corpusomatic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include util/CMakeFiles/corpusomatic.dir/compiler_depend.make

# Include the progress variables for this target.
include util/CMakeFiles/corpusomatic.dir/progress.make

# Include the compile flags for this target's objects.
include util/CMakeFiles/corpusomatic.dir/flags.make

util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o: util/CMakeFiles/corpusomatic.dir/flags.make
util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o: util/ng_corpus_editor.cpp
util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o: util/CMakeFiles/corpusomatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o -MF CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o.d -o CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o -c /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_editor.cpp

util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.i"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_editor.cpp > CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.i

util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.s"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_editor.cpp -o CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.s

util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o: util/CMakeFiles/corpusomatic.dir/flags.make
util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o: util/ng_corpus_generator.cpp
util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o: util/CMakeFiles/corpusomatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o -MF CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o.d -o CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o -c /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_generator.cpp

util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.i"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_generator.cpp > CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.i

util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.s"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_generator.cpp -o CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.s

util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o: util/CMakeFiles/corpusomatic.dir/flags.make
util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o: util/ng_corpus_properties.cpp
util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o: util/CMakeFiles/corpusomatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o -MF CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o.d -o CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o -c /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_properties.cpp

util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.i"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_properties.cpp > CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.i

util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.s"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_corpus_properties.cpp -o CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.s

util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o: util/CMakeFiles/corpusomatic.dir/flags.make
util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o: util/ng_find_matches.cpp
util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o: util/CMakeFiles/corpusomatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o -MF CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o.d -o CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o -c /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_find_matches.cpp

util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.i"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_find_matches.cpp > CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.i

util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.s"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/ng_find_matches.cpp -o CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.s

# Object files for target corpusomatic
corpusomatic_OBJECTS = \
"CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o" \
"CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o" \
"CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o" \
"CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o"

# External object files for target corpusomatic
corpusomatic_EXTERNAL_OBJECTS =

lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/ng_corpus_editor.cpp.o
lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/ng_corpus_generator.cpp.o
lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/ng_corpus_properties.cpp.o
lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/ng_find_matches.cpp.o
lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/build.make
lib/libcorpusomatic.a: util/CMakeFiles/corpusomatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../lib/libcorpusomatic.a"
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && $(CMAKE_COMMAND) -P CMakeFiles/corpusomatic.dir/cmake_clean_target.cmake
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/corpusomatic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
util/CMakeFiles/corpusomatic.dir/build: lib/libcorpusomatic.a
.PHONY : util/CMakeFiles/corpusomatic.dir/build

util/CMakeFiles/corpusomatic.dir/clean:
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util && $(CMAKE_COMMAND) -P CMakeFiles/corpusomatic.dir/cmake_clean.cmake
.PHONY : util/CMakeFiles/corpusomatic.dir/clean

util/CMakeFiles/corpusomatic.dir/depend:
	cd /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0 /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util /root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/util/CMakeFiles/corpusomatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : util/CMakeFiles/corpusomatic.dir/depend

