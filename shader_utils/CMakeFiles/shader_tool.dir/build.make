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
include shader_utils/CMakeFiles/shader_tool.dir/depend.make

# Include the progress variables for this target.
include shader_utils/CMakeFiles/shader_tool.dir/progress.make

# Include the compile flags for this target's objects.
include shader_utils/CMakeFiles/shader_tool.dir/flags.make

shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.o: shader_utils/CMakeFiles/shader_tool.dir/flags.make
shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.o: shader_utils/src/exceptions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shader_tool.dir/src/exceptions.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/exceptions.cpp

shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shader_tool.dir/src/exceptions.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/exceptions.cpp > CMakeFiles/shader_tool.dir/src/exceptions.cpp.i

shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shader_tool.dir/src/exceptions.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/exceptions.cpp -o CMakeFiles/shader_tool.dir/src/exceptions.cpp.s

shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.o: shader_utils/CMakeFiles/shader_tool.dir/flags.make
shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.o: shader_utils/src/program.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shader_tool.dir/src/program.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/program.cpp

shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shader_tool.dir/src/program.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/program.cpp > CMakeFiles/shader_tool.dir/src/program.cpp.i

shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shader_tool.dir/src/program.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/program.cpp -o CMakeFiles/shader_tool.dir/src/program.cpp.s

shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.o: shader_utils/CMakeFiles/shader_tool.dir/flags.make
shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.o: shader_utils/src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shader_tool.dir/src/shader.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader.cpp

shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shader_tool.dir/src/shader.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader.cpp > CMakeFiles/shader_tool.dir/src/shader.cpp.i

shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shader_tool.dir/src/shader.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader.cpp -o CMakeFiles/shader_tool.dir/src/shader.cpp.s

shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o: shader_utils/CMakeFiles/shader_tool.dir/flags.make
shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o: shader_utils/src/shader_tool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o -c /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader_tool.cpp

shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shader_tool.dir/src/shader_tool.cpp.i"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader_tool.cpp > CMakeFiles/shader_tool.dir/src/shader_tool.cpp.i

shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shader_tool.dir/src/shader_tool.cpp.s"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fuzzy/projects/opengl_code/learngl/shader_utils/src/shader_tool.cpp -o CMakeFiles/shader_tool.dir/src/shader_tool.cpp.s

# Object files for target shader_tool
shader_tool_OBJECTS = \
"CMakeFiles/shader_tool.dir/src/exceptions.cpp.o" \
"CMakeFiles/shader_tool.dir/src/program.cpp.o" \
"CMakeFiles/shader_tool.dir/src/shader.cpp.o" \
"CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o"

# External object files for target shader_tool
shader_tool_EXTERNAL_OBJECTS =

shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/src/exceptions.cpp.o
shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/src/program.cpp.o
shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/src/shader.cpp.o
shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/src/shader_tool.cpp.o
shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/build.make
shader_utils/libshader_tool.a: shader_utils/CMakeFiles/shader_tool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fuzzy/projects/opengl_code/learngl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libshader_tool.a"
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && $(CMAKE_COMMAND) -P CMakeFiles/shader_tool.dir/cmake_clean_target.cmake
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shader_tool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
shader_utils/CMakeFiles/shader_tool.dir/build: shader_utils/libshader_tool.a

.PHONY : shader_utils/CMakeFiles/shader_tool.dir/build

shader_utils/CMakeFiles/shader_tool.dir/clean:
	cd /home/fuzzy/projects/opengl_code/learngl/shader_utils && $(CMAKE_COMMAND) -P CMakeFiles/shader_tool.dir/cmake_clean.cmake
.PHONY : shader_utils/CMakeFiles/shader_tool.dir/clean

shader_utils/CMakeFiles/shader_tool.dir/depend:
	cd /home/fuzzy/projects/opengl_code/learngl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/shader_utils /home/fuzzy/projects/opengl_code/learngl /home/fuzzy/projects/opengl_code/learngl/shader_utils /home/fuzzy/projects/opengl_code/learngl/shader_utils/CMakeFiles/shader_tool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : shader_utils/CMakeFiles/shader_tool.dir/depend

