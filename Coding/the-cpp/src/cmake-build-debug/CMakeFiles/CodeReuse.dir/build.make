# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\IDE\CLion\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = E:\IDE\CLion\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Note\Note\Coding\the-cpp\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Note\Note\Coding\the-cpp\src\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CodeReuse.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/CodeReuse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CodeReuse.dir/flags.make

CMakeFiles/CodeReuse.dir/Unit6/main.cpp.obj: CMakeFiles/CodeReuse.dir/flags.make
CMakeFiles/CodeReuse.dir/Unit6/main.cpp.obj: ../Unit6/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CodeReuse.dir/Unit6/main.cpp.obj"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\CodeReuse.dir\Unit6\main.cpp.obj -c E:\Note\Note\Coding\the-cpp\src\Unit6\main.cpp

CMakeFiles/CodeReuse.dir/Unit6/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CodeReuse.dir/Unit6/main.cpp.i"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Note\Note\Coding\the-cpp\src\Unit6\main.cpp > CMakeFiles\CodeReuse.dir\Unit6\main.cpp.i

CMakeFiles/CodeReuse.dir/Unit6/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CodeReuse.dir/Unit6/main.cpp.s"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Note\Note\Coding\the-cpp\src\Unit6\main.cpp -o CMakeFiles\CodeReuse.dir\Unit6\main.cpp.s

# Object files for target CodeReuse
CodeReuse_OBJECTS = \
"CMakeFiles/CodeReuse.dir/Unit6/main.cpp.obj"

# External object files for target CodeReuse
CodeReuse_EXTERNAL_OBJECTS =

CodeReuse.exe: CMakeFiles/CodeReuse.dir/Unit6/main.cpp.obj
CodeReuse.exe: CMakeFiles/CodeReuse.dir/build.make
CodeReuse.exe: CMakeFiles/CodeReuse.dir/linklibs.rsp
CodeReuse.exe: CMakeFiles/CodeReuse.dir/objects1.rsp
CodeReuse.exe: CMakeFiles/CodeReuse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CodeReuse.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CodeReuse.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CodeReuse.dir/build: CodeReuse.exe
.PHONY : CMakeFiles/CodeReuse.dir/build

CMakeFiles/CodeReuse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CodeReuse.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CodeReuse.dir/clean

CMakeFiles/CodeReuse.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles\CodeReuse.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CodeReuse.dir/depend

