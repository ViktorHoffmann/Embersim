# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/viktor/programs/Embersim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/viktor/programs/Embersim/build

# Include any dependencies generated for this target.
include CMakeFiles/Embersim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Embersim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Embersim.dir/flags.make

CMakeFiles/Embersim.dir/Embersim.cpp.o: CMakeFiles/Embersim.dir/flags.make
CMakeFiles/Embersim.dir/Embersim.cpp.o: ../Embersim.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/viktor/programs/Embersim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Embersim.dir/Embersim.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Embersim.dir/Embersim.cpp.o -c /home/viktor/programs/Embersim/Embersim.cpp

CMakeFiles/Embersim.dir/Embersim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Embersim.dir/Embersim.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/viktor/programs/Embersim/Embersim.cpp > CMakeFiles/Embersim.dir/Embersim.cpp.i

CMakeFiles/Embersim.dir/Embersim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Embersim.dir/Embersim.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/viktor/programs/Embersim/Embersim.cpp -o CMakeFiles/Embersim.dir/Embersim.cpp.s

# Object files for target Embersim
Embersim_OBJECTS = \
"CMakeFiles/Embersim.dir/Embersim.cpp.o"

# External object files for target Embersim
Embersim_EXTERNAL_OBJECTS =

Embersim: CMakeFiles/Embersim.dir/Embersim.cpp.o
Embersim: CMakeFiles/Embersim.dir/build.make
Embersim: CMakeFiles/Embersim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/viktor/programs/Embersim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Embersim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Embersim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Embersim.dir/build: Embersim

.PHONY : CMakeFiles/Embersim.dir/build

CMakeFiles/Embersim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Embersim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Embersim.dir/clean

CMakeFiles/Embersim.dir/depend:
	cd /home/viktor/programs/Embersim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/viktor/programs/Embersim /home/viktor/programs/Embersim /home/viktor/programs/Embersim/build /home/viktor/programs/Embersim/build /home/viktor/programs/Embersim/build/CMakeFiles/Embersim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Embersim.dir/depend
