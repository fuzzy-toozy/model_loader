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
CMAKE_SOURCE_DIR = /home/fuzzy/projects/opengl_code/learngl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fuzzy/projects/opengl_code/learngl

# Include any dependencies generated for this target.
include graphic_control/CMakeFiles/graphic_control.dir/depend.make

# Include the progress variables for this target.
include graphic_control/CMakeFiles/graphic_control.dir/progress.make

# Include the compile flags for this target's objects.
include graphic_control/CMakeFiles/graphic_control.dir/flags.make

graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.o: graphic_control/CMakeFiles/graphic_control.dir/flags.make
graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.o: graphic_control/src/program.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphic_control.dir/src/program.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/graphic_control/src/program.cpp

graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphic_control.dir/src/program.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/graphic_control/src/program.cpp > CMakeFiles/graphic_control.dir/src/program.cpp.i

graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphic_control.dir/src/program.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/graphic_control/src/program.cpp -o CMakeFiles/graphic_control.dir/src/program.cpp.s

# Object files for target graphic_control
graphic_control_OBJECTS = \
"CMakeFiles/graphic_control.dir/src/program.cpp.o"

# External object files for target graphic_control
graphic_control_EXTERNAL_OBJECTS =

graphic_control/libgraphic_control.a: graphic_control/CMakeFiles/graphic_control.dir/src/program.cpp.o
graphic_control/libgraphic_control.a: graphic_control/CMakeFiles/graphic_control.dir/build.make
graphic_control/libgraphic_control.a: graphic_control/CMakeFiles/graphic_control.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgraphic_control.a"
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && $(CMAKE_COMMAND) -P CMakeFiles/graphic_control.dir/cmake_clean_target.cmake
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphic_control.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
graphic_control/CMakeFiles/graphic_control.dir/build: graphic_control/libgraphic_control.a

.PHONY : graphic_control/CMakeFiles/graphic_control.dir/build

graphic_control/CMakeFiles/graphic_control.dir/clean:
	cd /home/fuzzy/projects/opengl_code/learngl/graphic_control && $(CMAKE_COMMAND) -P CMakeFiles/graphic_control.dir/cmake_clean.cmake
.PHONY : graphic_control/CMakeFiles/graphic_control.dir/clean

graphic_control/CMakeFiles/graphic_control.dir/depend:
	cd /home/fuzzy/projects/opengl_code/learngl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/graphic_control /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/graphic_control /home/fuzzy/projects/opengl_code/learngl/graphic_control/CMakeFiles/graphic_control.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : graphic_control/CMakeFiles/graphic_control.dir/depend

