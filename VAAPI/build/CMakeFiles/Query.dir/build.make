# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /run/media/ethanw/LinuxGames/Repos/enc/VAAPI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build

# Include any dependencies generated for this target.
include CMakeFiles/Query.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Query.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Query.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Query.dir/flags.make

CMakeFiles/Query.dir/Query.cpp.o: CMakeFiles/Query.dir/flags.make
CMakeFiles/Query.dir/Query.cpp.o: /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/Query.cpp
CMakeFiles/Query.dir/Query.cpp.o: CMakeFiles/Query.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Query.dir/Query.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Query.dir/Query.cpp.o -MF CMakeFiles/Query.dir/Query.cpp.o.d -o CMakeFiles/Query.dir/Query.cpp.o -c /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/Query.cpp

CMakeFiles/Query.dir/Query.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Query.dir/Query.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/Query.cpp > CMakeFiles/Query.dir/Query.cpp.i

CMakeFiles/Query.dir/Query.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Query.dir/Query.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/Query.cpp -o CMakeFiles/Query.dir/Query.cpp.s

# Object files for target Query
Query_OBJECTS = \
"CMakeFiles/Query.dir/Query.cpp.o"

# External object files for target Query
Query_EXTERNAL_OBJECTS =

Query: CMakeFiles/Query.dir/Query.cpp.o
Query: CMakeFiles/Query.dir/build.make
Query: CMakeFiles/Query.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Query"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Query.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Query.dir/build: Query
.PHONY : CMakeFiles/Query.dir/build

CMakeFiles/Query.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Query.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Query.dir/clean

CMakeFiles/Query.dir/depend:
	cd /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/ethanw/LinuxGames/Repos/enc/VAAPI /run/media/ethanw/LinuxGames/Repos/enc/VAAPI /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build /run/media/ethanw/LinuxGames/Repos/enc/VAAPI/build/CMakeFiles/Query.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Query.dir/depend

