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
CMAKE_SOURCE_DIR = /mnt/sda3/Repos/enc/Vulkan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/sda3/Repos/enc/Vulkan/build

# Include any dependencies generated for this target.
include CMakeFiles/conv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/conv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/conv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conv.dir/flags.make

CMakeFiles/conv.dir/main.cpp.o: CMakeFiles/conv.dir/flags.make
CMakeFiles/conv.dir/main.cpp.o: /mnt/sda3/Repos/enc/Vulkan/main.cpp
CMakeFiles/conv.dir/main.cpp.o: CMakeFiles/conv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/sda3/Repos/enc/Vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/conv.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/conv.dir/main.cpp.o -MF CMakeFiles/conv.dir/main.cpp.o.d -o CMakeFiles/conv.dir/main.cpp.o -c /mnt/sda3/Repos/enc/Vulkan/main.cpp

CMakeFiles/conv.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conv.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/sda3/Repos/enc/Vulkan/main.cpp > CMakeFiles/conv.dir/main.cpp.i

CMakeFiles/conv.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conv.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/sda3/Repos/enc/Vulkan/main.cpp -o CMakeFiles/conv.dir/main.cpp.s

# Object files for target conv
conv_OBJECTS = \
"CMakeFiles/conv.dir/main.cpp.o"

# External object files for target conv
conv_EXTERNAL_OBJECTS =

conv: CMakeFiles/conv.dir/main.cpp.o
conv: CMakeFiles/conv.dir/build.make
conv: CMakeFiles/conv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/sda3/Repos/enc/Vulkan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable conv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conv.dir/build: conv
.PHONY : CMakeFiles/conv.dir/build

CMakeFiles/conv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conv.dir/clean

CMakeFiles/conv.dir/depend:
	cd /mnt/sda3/Repos/enc/Vulkan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/sda3/Repos/enc/Vulkan /mnt/sda3/Repos/enc/Vulkan /mnt/sda3/Repos/enc/Vulkan/build /mnt/sda3/Repos/enc/Vulkan/build /mnt/sda3/Repos/enc/Vulkan/build/CMakeFiles/conv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conv.dir/depend

