# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/adisteyf/apps/cpp/cfiles-engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adisteyf/apps/cpp/cfiles-engine/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/codegen:
.PHONY : CMakeFiles/main.dir/codegen

CMakeFiles/main.dir/src/EBO.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/EBO.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/EBO.cpp
CMakeFiles/main.dir/src/EBO.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/EBO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/EBO.cpp.o -MF CMakeFiles/main.dir/src/EBO.cpp.o.d -o CMakeFiles/main.dir/src/EBO.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/EBO.cpp

CMakeFiles/main.dir/src/EBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/EBO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/EBO.cpp > CMakeFiles/main.dir/src/EBO.cpp.i

CMakeFiles/main.dir/src/EBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/EBO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/EBO.cpp -o CMakeFiles/main.dir/src/EBO.cpp.s

CMakeFiles/main.dir/src/VAO.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/VAO.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/VAO.cpp
CMakeFiles/main.dir/src/VAO.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/VAO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/VAO.cpp.o -MF CMakeFiles/main.dir/src/VAO.cpp.o.d -o CMakeFiles/main.dir/src/VAO.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/VAO.cpp

CMakeFiles/main.dir/src/VAO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/VAO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/VAO.cpp > CMakeFiles/main.dir/src/VAO.cpp.i

CMakeFiles/main.dir/src/VAO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/VAO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/VAO.cpp -o CMakeFiles/main.dir/src/VAO.cpp.s

CMakeFiles/main.dir/src/VBO.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/VBO.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/VBO.cpp
CMakeFiles/main.dir/src/VBO.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/VBO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/VBO.cpp.o -MF CMakeFiles/main.dir/src/VBO.cpp.o.d -o CMakeFiles/main.dir/src/VBO.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/VBO.cpp

CMakeFiles/main.dir/src/VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/VBO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/VBO.cpp > CMakeFiles/main.dir/src/VBO.cpp.i

CMakeFiles/main.dir/src/VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/VBO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/VBO.cpp -o CMakeFiles/main.dir/src/VBO.cpp.s

CMakeFiles/main.dir/src/boot.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/boot.c.o: /home/adisteyf/apps/cpp/cfiles-engine/src/boot.c
CMakeFiles/main.dir/src/boot.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/src/boot.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/boot.c.o -MF CMakeFiles/main.dir/src/boot.c.o.d -o CMakeFiles/main.dir/src/boot.c.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/boot.c

CMakeFiles/main.dir/src/boot.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/boot.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/boot.c > CMakeFiles/main.dir/src/boot.c.i

CMakeFiles/main.dir/src/boot.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/boot.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/boot.c -o CMakeFiles/main.dir/src/boot.c.s

CMakeFiles/main.dir/src/camera.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/camera.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/camera.cpp
CMakeFiles/main.dir/src/camera.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/camera.cpp.o -MF CMakeFiles/main.dir/src/camera.cpp.o.d -o CMakeFiles/main.dir/src/camera.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/camera.cpp

CMakeFiles/main.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/camera.cpp > CMakeFiles/main.dir/src/camera.cpp.i

CMakeFiles/main.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/camera.cpp -o CMakeFiles/main.dir/src/camera.cpp.s

CMakeFiles/main.dir/src/debug.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/debug.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/debug.cpp
CMakeFiles/main.dir/src/debug.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/debug.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/debug.cpp.o -MF CMakeFiles/main.dir/src/debug.cpp.o.d -o CMakeFiles/main.dir/src/debug.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/debug.cpp

CMakeFiles/main.dir/src/debug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/debug.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/debug.cpp > CMakeFiles/main.dir/src/debug.cpp.i

CMakeFiles/main.dir/src/debug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/debug.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/debug.cpp -o CMakeFiles/main.dir/src/debug.cpp.s

CMakeFiles/main.dir/src/glad.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/glad.c.o: /home/adisteyf/apps/cpp/cfiles-engine/src/glad.c
CMakeFiles/main.dir/src/glad.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/main.dir/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/glad.c.o -MF CMakeFiles/main.dir/src/glad.c.o.d -o CMakeFiles/main.dir/src/glad.c.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/glad.c

CMakeFiles/main.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/glad.c > CMakeFiles/main.dir/src/glad.c.i

CMakeFiles/main.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/glad.c -o CMakeFiles/main.dir/src/glad.c.s

CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/main.cpp
CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.cpp.o -MF CMakeFiles/main.dir/src/main.cpp.o.d -o CMakeFiles/main.dir/src/main.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/main.cpp

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/main.cpp > CMakeFiles/main.dir/src/main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/main.cpp -o CMakeFiles/main.dir/src/main.cpp.s

CMakeFiles/main.dir/src/mesh.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/mesh.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/mesh.cpp
CMakeFiles/main.dir/src/mesh.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/src/mesh.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/mesh.cpp.o -MF CMakeFiles/main.dir/src/mesh.cpp.o.d -o CMakeFiles/main.dir/src/mesh.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/mesh.cpp

CMakeFiles/main.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/mesh.cpp > CMakeFiles/main.dir/src/mesh.cpp.i

CMakeFiles/main.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/mesh.cpp -o CMakeFiles/main.dir/src/mesh.cpp.s

CMakeFiles/main.dir/src/model.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/model.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/model.cpp
CMakeFiles/main.dir/src/model.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/src/model.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/model.cpp.o -MF CMakeFiles/main.dir/src/model.cpp.o.d -o CMakeFiles/main.dir/src/model.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/model.cpp

CMakeFiles/main.dir/src/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/model.cpp > CMakeFiles/main.dir/src/model.cpp.i

CMakeFiles/main.dir/src/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/model.cpp -o CMakeFiles/main.dir/src/model.cpp.s

CMakeFiles/main.dir/src/shader.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/shader.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/shader.cpp
CMakeFiles/main.dir/src/shader.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/src/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/shader.cpp.o -MF CMakeFiles/main.dir/src/shader.cpp.o.d -o CMakeFiles/main.dir/src/shader.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/shader.cpp

CMakeFiles/main.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/shader.cpp > CMakeFiles/main.dir/src/shader.cpp.i

CMakeFiles/main.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/shader.cpp -o CMakeFiles/main.dir/src/shader.cpp.s

CMakeFiles/main.dir/src/stb.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/stb.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/stb.cpp
CMakeFiles/main.dir/src/stb.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/main.dir/src/stb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/stb.cpp.o -MF CMakeFiles/main.dir/src/stb.cpp.o.d -o CMakeFiles/main.dir/src/stb.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/stb.cpp

CMakeFiles/main.dir/src/stb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/stb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/stb.cpp > CMakeFiles/main.dir/src/stb.cpp.i

CMakeFiles/main.dir/src/stb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/stb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/stb.cpp -o CMakeFiles/main.dir/src/stb.cpp.s

CMakeFiles/main.dir/src/texture.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/texture.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/texture.cpp
CMakeFiles/main.dir/src/texture.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/main.dir/src/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/texture.cpp.o -MF CMakeFiles/main.dir/src/texture.cpp.o.d -o CMakeFiles/main.dir/src/texture.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/texture.cpp

CMakeFiles/main.dir/src/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/texture.cpp > CMakeFiles/main.dir/src/texture.cpp.i

CMakeFiles/main.dir/src/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/texture.cpp -o CMakeFiles/main.dir/src/texture.cpp.s

CMakeFiles/main.dir/src/window.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/window.cpp.o: /home/adisteyf/apps/cpp/cfiles-engine/src/window.cpp
CMakeFiles/main.dir/src/window.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/main.dir/src/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/window.cpp.o -MF CMakeFiles/main.dir/src/window.cpp.o.d -o CMakeFiles/main.dir/src/window.cpp.o -c /home/adisteyf/apps/cpp/cfiles-engine/src/window.cpp

CMakeFiles/main.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adisteyf/apps/cpp/cfiles-engine/src/window.cpp > CMakeFiles/main.dir/src/window.cpp.i

CMakeFiles/main.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adisteyf/apps/cpp/cfiles-engine/src/window.cpp -o CMakeFiles/main.dir/src/window.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/EBO.cpp.o" \
"CMakeFiles/main.dir/src/VAO.cpp.o" \
"CMakeFiles/main.dir/src/VBO.cpp.o" \
"CMakeFiles/main.dir/src/boot.c.o" \
"CMakeFiles/main.dir/src/camera.cpp.o" \
"CMakeFiles/main.dir/src/debug.cpp.o" \
"CMakeFiles/main.dir/src/glad.c.o" \
"CMakeFiles/main.dir/src/main.cpp.o" \
"CMakeFiles/main.dir/src/mesh.cpp.o" \
"CMakeFiles/main.dir/src/model.cpp.o" \
"CMakeFiles/main.dir/src/shader.cpp.o" \
"CMakeFiles/main.dir/src/stb.cpp.o" \
"CMakeFiles/main.dir/src/texture.cpp.o" \
"CMakeFiles/main.dir/src/window.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/EBO.cpp.o
main: CMakeFiles/main.dir/src/VAO.cpp.o
main: CMakeFiles/main.dir/src/VBO.cpp.o
main: CMakeFiles/main.dir/src/boot.c.o
main: CMakeFiles/main.dir/src/camera.cpp.o
main: CMakeFiles/main.dir/src/debug.cpp.o
main: CMakeFiles/main.dir/src/glad.c.o
main: CMakeFiles/main.dir/src/main.cpp.o
main: CMakeFiles/main.dir/src/mesh.cpp.o
main: CMakeFiles/main.dir/src/model.cpp.o
main: CMakeFiles/main.dir/src/shader.cpp.o
main: CMakeFiles/main.dir/src/stb.cpp.o
main: CMakeFiles/main.dir/src/texture.cpp.o
main: CMakeFiles/main.dir/src/window.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/compiler_depend.ts
main: /usr/lib/libGL.so
main: /usr/lib/libGLU.so
main: /usr/lib/libglfw.so.3.4
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/adisteyf/apps/cpp/cfiles-engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adisteyf/apps/cpp/cfiles-engine /home/adisteyf/apps/cpp/cfiles-engine /home/adisteyf/apps/cpp/cfiles-engine/build /home/adisteyf/apps/cpp/cfiles-engine/build /home/adisteyf/apps/cpp/cfiles-engine/build/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

