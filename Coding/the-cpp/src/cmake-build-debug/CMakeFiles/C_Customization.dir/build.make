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
include CMakeFiles/C_Customization.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/C_Customization.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C_Customization.dir/flags.make

CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.obj: CMakeFiles/C_Customization.dir/flags.make
CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.obj: ../Unit2/Class\ Flexible\ Demo/complex_c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.obj"
	E:\DevelopmentKit\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\C_Customization.dir\Unit2\Class_Flexible_Demo\complex_c.c.obj -c "E:\Note\Note\Coding\the-cpp\src\Unit2\Class Flexible Demo\complex_c.c"

CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.i"
	E:\DevelopmentKit\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "E:\Note\Note\Coding\the-cpp\src\Unit2\Class Flexible Demo\complex_c.c" > CMakeFiles\C_Customization.dir\Unit2\Class_Flexible_Demo\complex_c.c.i

CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.s"
	E:\DevelopmentKit\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "E:\Note\Note\Coding\the-cpp\src\Unit2\Class Flexible Demo\complex_c.c" -o CMakeFiles\C_Customization.dir\Unit2\Class_Flexible_Demo\complex_c.c.s

# Object files for target C_Customization
C_Customization_OBJECTS = \
"CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.obj"

# External object files for target C_Customization
C_Customization_EXTERNAL_OBJECTS =

C_Customization.exe: CMakeFiles/C_Customization.dir/Unit2/Class_Flexible_Demo/complex_c.c.obj
C_Customization.exe: CMakeFiles/C_Customization.dir/build.make
C_Customization.exe: CMakeFiles/C_Customization.dir/linklibs.rsp
C_Customization.exe: CMakeFiles/C_Customization.dir/objects1.rsp
C_Customization.exe: CMakeFiles/C_Customization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable C_Customization.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\C_Customization.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C_Customization.dir/build: C_Customization.exe
.PHONY : CMakeFiles/C_Customization.dir/build

CMakeFiles/C_Customization.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\C_Customization.dir\cmake_clean.cmake
.PHONY : CMakeFiles/C_Customization.dir/clean

CMakeFiles/C_Customization.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug E:\Note\Note\Coding\the-cpp\src\cmake-build-debug\CMakeFiles\C_Customization.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C_Customization.dir/depend

