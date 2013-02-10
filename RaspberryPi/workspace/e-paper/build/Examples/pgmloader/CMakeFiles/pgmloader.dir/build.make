# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/siddian/src/asrp/RaspberryPi/workspace/e-paper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build

# Include any dependencies generated for this target.
include Examples/pgmloader/CMakeFiles/pgmloader.dir/depend.make

# Include the progress variables for this target.
include Examples/pgmloader/CMakeFiles/pgmloader.dir/progress.make

# Include the compile flags for this target's objects.
include Examples/pgmloader/CMakeFiles/pgmloader.dir/flags.make

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o: Examples/pgmloader/CMakeFiles/pgmloader.dir/flags.make
Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o: ../Examples/pgmloader/e-paper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o"
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pgmloader.dir/e-paper.cpp.o -c /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/Examples/pgmloader/e-paper.cpp

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pgmloader.dir/e-paper.cpp.i"
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/Examples/pgmloader/e-paper.cpp > CMakeFiles/pgmloader.dir/e-paper.cpp.i

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pgmloader.dir/e-paper.cpp.s"
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/Examples/pgmloader/e-paper.cpp -o CMakeFiles/pgmloader.dir/e-paper.cpp.s

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.requires:
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.requires

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.provides: Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.requires
	$(MAKE) -f Examples/pgmloader/CMakeFiles/pgmloader.dir/build.make Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.provides.build
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.provides

Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.provides.build: Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o

# Object files for target pgmloader
pgmloader_OBJECTS = \
"CMakeFiles/pgmloader.dir/e-paper.cpp.o"

# External object files for target pgmloader
pgmloader_EXTERNAL_OBJECTS =

Examples/pgmloader/pgmloader: Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o
Examples/pgmloader/pgmloader: EPlibrary/libePaper.a
Examples/pgmloader/pgmloader: Examples/pgmloader/CMakeFiles/pgmloader.dir/build.make
Examples/pgmloader/pgmloader: Examples/pgmloader/CMakeFiles/pgmloader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable pgmloader"
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pgmloader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Examples/pgmloader/CMakeFiles/pgmloader.dir/build: Examples/pgmloader/pgmloader
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/build

Examples/pgmloader/CMakeFiles/pgmloader.dir/requires: Examples/pgmloader/CMakeFiles/pgmloader.dir/e-paper.cpp.o.requires
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/requires

Examples/pgmloader/CMakeFiles/pgmloader.dir/clean:
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader && $(CMAKE_COMMAND) -P CMakeFiles/pgmloader.dir/cmake_clean.cmake
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/clean

Examples/pgmloader/CMakeFiles/pgmloader.dir/depend:
	cd /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/siddian/src/asrp/RaspberryPi/workspace/e-paper /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/Examples/pgmloader /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader /home/siddian/src/asrp/RaspberryPi/workspace/e-paper/build/Examples/pgmloader/CMakeFiles/pgmloader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Examples/pgmloader/CMakeFiles/pgmloader.dir/depend

