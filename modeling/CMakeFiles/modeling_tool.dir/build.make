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
include modeling/CMakeFiles/modeling_tool.dir/depend.make

# Include the progress variables for this target.
include modeling/CMakeFiles/modeling_tool.dir/progress.make

# Include the compile flags for this target's objects.
include modeling/CMakeFiles/modeling_tool.dir/flags.make

modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.o: modeling/CMakeFiles/modeling_tool.dir/flags.make
modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.o: modeling/src/mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modeling_tool.dir/src/mesh.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/modeling/src/mesh.cpp

modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modeling_tool.dir/src/mesh.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/modeling/src/mesh.cpp > CMakeFiles/modeling_tool.dir/src/mesh.cpp.i

modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modeling_tool.dir/src/mesh.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/modeling/src/mesh.cpp -o CMakeFiles/modeling_tool.dir/src/mesh.cpp.s

modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.o: modeling/CMakeFiles/modeling_tool.dir/flags.make
modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.o: modeling/src/model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modeling_tool.dir/src/model.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/modeling/src/model.cpp

modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modeling_tool.dir/src/model.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/modeling/src/model.cpp > CMakeFiles/modeling_tool.dir/src/model.cpp.i

modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modeling_tool.dir/src/model.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/modeling/src/model.cpp -o CMakeFiles/modeling_tool.dir/src/model.cpp.s

# Object files for target modeling_tool
modeling_tool_OBJECTS = \
"CMakeFiles/modeling_tool.dir/src/mesh.cpp.o" \
"CMakeFiles/modeling_tool.dir/src/model.cpp.o"

# External object files for target modeling_tool
modeling_tool_EXTERNAL_OBJECTS =

modeling/libmodeling_tool.a: modeling/CMakeFiles/modeling_tool.dir/src/mesh.cpp.o
modeling/libmodeling_tool.a: modeling/CMakeFiles/modeling_tool.dir/src/model.cpp.o
modeling/libmodeling_tool.a: modeling/CMakeFiles/modeling_tool.dir/build.make
modeling/libmodeling_tool.a: modeling/CMakeFiles/modeling_tool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmodeling_tool.a"
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && $(CMAKE_COMMAND) -P CMakeFiles/modeling_tool.dir/cmake_clean_target.cmake
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modeling_tool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modeling/CMakeFiles/modeling_tool.dir/build: modeling/libmodeling_tool.a

.PHONY : modeling/CMakeFiles/modeling_tool.dir/build

modeling/CMakeFiles/modeling_tool.dir/clean:
	cd /home/fuzzy/projects/opengl_code/learngl/modeling && $(CMAKE_COMMAND) -P CMakeFiles/modeling_tool.dir/cmake_clean.cmake
.PHONY : modeling/CMakeFiles/modeling_tool.dir/clean

modeling/CMakeFiles/modeling_tool.dir/depend:
	cd /home/fuzzy/projects/opengl_code/learngl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/modeling /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/modeling /home/fuzzy/projects/opengl_code/learngl/modeling/CMakeFiles/modeling_tool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modeling/CMakeFiles/modeling_tool.dir/depend

