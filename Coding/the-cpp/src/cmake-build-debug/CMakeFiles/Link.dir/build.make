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
include CMakeFiles/Link.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Link.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Link.dir/flags.make

CMakeFiles/Link.dir/Unit1/Link/link1.cpp.obj: CMakeFiles/Link.dir/flags.make
CMakeFiles/Link.dir/Unit1/Link/link1.cpp.obj: ../Unit1/Link/link1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Link.dir/Unit1/Link/link1.cpp.obj"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Link.dir\Unit1\Link\link1.cpp.obj -c E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link1.cpp

CMakeFiles/Link.dir/Unit1/Link/link1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Link.dir/Unit1/Link/link1.cpp.i"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link1.cpp > CMakeFiles\Link.dir\Unit1\Link\link1.cpp.i

CMakeFiles/Link.dir/Unit1/Link/link1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Link.dir/Unit1/Link/link1.cpp.s"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link1.cpp -o CMakeFiles\Link.dir\Unit1\Link\link1.cpp.s

CMakeFiles/Link.dir/Unit1/Link/link2.cpp.obj: CMakeFiles/Link.dir/flags.make
CMakeFiles/Link.dir/Unit1/Link/link2.cpp.obj: ../Unit1/Link/link2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Link.dir/Unit1/Link/link2.cpp.obj"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Link.dir\Unit1\Link\link2.cpp.obj -c E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link2.cpp

CMakeFiles/Link.dir/Unit1/Link/link2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Link.dir/Unit1/Link/link2.cpp.i"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link2.cpp > CMakeFiles\Link.dir\Unit1\Link\link2.cpp.i

CMakeFiles/Link.dir/Unit1/Link/link2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Link.dir/Unit1/Link/link2.cpp.s"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Note\Note\Coding\the-cpp\src\Unit1\Link\link2.cpp -o CMakeFiles\Link.dir\Unit1\Link\link2.cpp.s

# Object files for target Link
Link_OBJECTS = \
"CMakeFiles/Link.dir/Unit1/Link/link1.cpp.obj" \
"CMakeFiles/Link.dir/Unit1/Link/link2.cpp.obj"

# External object files for target Link
Link_EXTERNAL_OBJECTS =

Link.exe: CMakeFiles/Link.dir/Unit1/Link/link1.cpp.obj
Link.exe: CMakeFiles/Link.dir/Unit1/Link/link2.cpp.obj
Link.exe: CMakeFiles/Link.dir/build.make
Link.exe: CMakeFiles/Link.dir/linklibs.rsp
Link.exe: CMakeFiles/Link.dir/objects1.rsp
Link.exe: CMakeFiles/Link.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Link.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Link.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Link.dir/build: Link.exe
.PHONY : CMakeFiles/Link.dir/build

CMakeFiles/Link.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Link.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Link.dir/clean

CMakeFiles/Link.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles\Link.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Link.dir/depend

