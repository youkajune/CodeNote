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
include CMakeFiles/ExceptionSTDClass.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ExceptionSTDClass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ExceptionSTDClass.dir/flags.make

CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.obj: CMakeFiles/ExceptionSTDClass.dir/flags.make
CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.obj: ../Unit8/ExceptionSTDClass/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.obj"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ExceptionSTDClass.dir\Unit8\ExceptionSTDClass\main.cpp.obj -c E:\Note\Note\Coding\the-cpp\src\Unit8\ExceptionSTDClass\main.cpp

CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.i"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Note\Note\Coding\the-cpp\src\Unit8\ExceptionSTDClass\main.cpp > CMakeFiles\ExceptionSTDClass.dir\Unit8\ExceptionSTDClass\main.cpp.i

CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.s"
	E:\DevelopmentKit\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Note\Note\Coding\the-cpp\src\Unit8\ExceptionSTDClass\main.cpp -o CMakeFiles\ExceptionSTDClass.dir\Unit8\ExceptionSTDClass\main.cpp.s

# Object files for target ExceptionSTDClass
ExceptionSTDClass_OBJECTS = \
"CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.obj"

# External object files for target ExceptionSTDClass
ExceptionSTDClass_EXTERNAL_OBJECTS =

ExceptionSTDClass.exe: CMakeFiles/ExceptionSTDClass.dir/Unit8/ExceptionSTDClass/main.cpp.obj
ExceptionSTDClass.exe: CMakeFiles/ExceptionSTDClass.dir/build.make
ExceptionSTDClass.exe: CMakeFiles/ExceptionSTDClass.dir/linklibs.rsp
ExceptionSTDClass.exe: CMakeFiles/ExceptionSTDClass.dir/objects1.rsp
ExceptionSTDClass.exe: CMakeFiles/ExceptionSTDClass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ExceptionSTDClass.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ExceptionSTDClass.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ExceptionSTDClass.dir/build: ExceptionSTDClass.exe
.PHONY : CMakeFiles/ExceptionSTDClass.dir/build

CMakeFiles/ExceptionSTDClass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ExceptionSTDClass.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ExceptionSTDClass.dir/clean

CMakeFiles/ExceptionSTDClass.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles\ExceptionSTDClass.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExceptionSTDClass.dir/depend

