# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/evan/CPE471/Lab01/L01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/evan/CPE471/Lab01/L01/build

# Include any dependencies generated for this target.
include CMakeFiles/Lab01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab01.dir/flags.make

CMakeFiles/Lab01.dir/src/Image.cpp.o: CMakeFiles/Lab01.dir/flags.make
CMakeFiles/Lab01.dir/src/Image.cpp.o: ../src/Image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/evan/CPE471/Lab01/L01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab01.dir/src/Image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab01.dir/src/Image.cpp.o -c /Users/evan/CPE471/Lab01/L01/src/Image.cpp

CMakeFiles/Lab01.dir/src/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab01.dir/src/Image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/evan/CPE471/Lab01/L01/src/Image.cpp > CMakeFiles/Lab01.dir/src/Image.cpp.i

CMakeFiles/Lab01.dir/src/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab01.dir/src/Image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/evan/CPE471/Lab01/L01/src/Image.cpp -o CMakeFiles/Lab01.dir/src/Image.cpp.s

CMakeFiles/Lab01.dir/src/Image.cpp.o.requires:

.PHONY : CMakeFiles/Lab01.dir/src/Image.cpp.o.requires

CMakeFiles/Lab01.dir/src/Image.cpp.o.provides: CMakeFiles/Lab01.dir/src/Image.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab01.dir/build.make CMakeFiles/Lab01.dir/src/Image.cpp.o.provides.build
.PHONY : CMakeFiles/Lab01.dir/src/Image.cpp.o.provides

CMakeFiles/Lab01.dir/src/Image.cpp.o.provides.build: CMakeFiles/Lab01.dir/src/Image.cpp.o


CMakeFiles/Lab01.dir/src/main.cpp.o: CMakeFiles/Lab01.dir/flags.make
CMakeFiles/Lab01.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/evan/CPE471/Lab01/L01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lab01.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab01.dir/src/main.cpp.o -c /Users/evan/CPE471/Lab01/L01/src/main.cpp

CMakeFiles/Lab01.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab01.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/evan/CPE471/Lab01/L01/src/main.cpp > CMakeFiles/Lab01.dir/src/main.cpp.i

CMakeFiles/Lab01.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab01.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/evan/CPE471/Lab01/L01/src/main.cpp -o CMakeFiles/Lab01.dir/src/main.cpp.s

CMakeFiles/Lab01.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/Lab01.dir/src/main.cpp.o.requires

CMakeFiles/Lab01.dir/src/main.cpp.o.provides: CMakeFiles/Lab01.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab01.dir/build.make CMakeFiles/Lab01.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Lab01.dir/src/main.cpp.o.provides

CMakeFiles/Lab01.dir/src/main.cpp.o.provides.build: CMakeFiles/Lab01.dir/src/main.cpp.o


# Object files for target Lab01
Lab01_OBJECTS = \
"CMakeFiles/Lab01.dir/src/Image.cpp.o" \
"CMakeFiles/Lab01.dir/src/main.cpp.o"

# External object files for target Lab01
Lab01_EXTERNAL_OBJECTS =

Lab01: CMakeFiles/Lab01.dir/src/Image.cpp.o
Lab01: CMakeFiles/Lab01.dir/src/main.cpp.o
Lab01: CMakeFiles/Lab01.dir/build.make
Lab01: CMakeFiles/Lab01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/evan/CPE471/Lab01/L01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Lab01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab01.dir/build: Lab01

.PHONY : CMakeFiles/Lab01.dir/build

CMakeFiles/Lab01.dir/requires: CMakeFiles/Lab01.dir/src/Image.cpp.o.requires
CMakeFiles/Lab01.dir/requires: CMakeFiles/Lab01.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/Lab01.dir/requires

CMakeFiles/Lab01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab01.dir/clean

CMakeFiles/Lab01.dir/depend:
	cd /Users/evan/CPE471/Lab01/L01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/evan/CPE471/Lab01/L01 /Users/evan/CPE471/Lab01/L01 /Users/evan/CPE471/Lab01/L01/build /Users/evan/CPE471/Lab01/L01/build /Users/evan/CPE471/Lab01/L01/build/CMakeFiles/Lab01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab01.dir/depend

