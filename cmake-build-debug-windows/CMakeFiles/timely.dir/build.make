# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/share/clion-2020.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/share/clion-2020.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/dev/c/timely-lang

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/dev/c/timely-lang/cmake-build-debug-windows

# Include any dependencies generated for this target.
include CMakeFiles/timely.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/timely.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/timely.dir/flags.make

CMakeFiles/timely.dir/main.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/timely.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/main.c.o   -c /mnt/dev/c/timely-lang/main.c

CMakeFiles/timely.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/main.c > CMakeFiles/timely.dir/main.c.i

CMakeFiles/timely.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/main.c -o CMakeFiles/timely.dir/main.c.s

CMakeFiles/timely.dir/lexer.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/lexer.c.o: ../lexer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/timely.dir/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/lexer.c.o   -c /mnt/dev/c/timely-lang/lexer.c

CMakeFiles/timely.dir/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/lexer.c > CMakeFiles/timely.dir/lexer.c.i

CMakeFiles/timely.dir/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/lexer.c -o CMakeFiles/timely.dir/lexer.c.s

CMakeFiles/timely.dir/list.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/list.c.o: ../list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/timely.dir/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/list.c.o   -c /mnt/dev/c/timely-lang/list.c

CMakeFiles/timely.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/list.c > CMakeFiles/timely.dir/list.c.i

CMakeFiles/timely.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/list.c -o CMakeFiles/timely.dir/list.c.s

CMakeFiles/timely.dir/basic.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/basic.c.o: ../basic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/timely.dir/basic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/basic.c.o   -c /mnt/dev/c/timely-lang/basic.c

CMakeFiles/timely.dir/basic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/basic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/basic.c > CMakeFiles/timely.dir/basic.c.i

CMakeFiles/timely.dir/basic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/basic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/basic.c -o CMakeFiles/timely.dir/basic.c.s

CMakeFiles/timely.dir/tree.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/tree.c.o: ../tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/timely.dir/tree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/tree.c.o   -c /mnt/dev/c/timely-lang/tree.c

CMakeFiles/timely.dir/tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/tree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/tree.c > CMakeFiles/timely.dir/tree.c.i

CMakeFiles/timely.dir/tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/tree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/tree.c -o CMakeFiles/timely.dir/tree.c.s

CMakeFiles/timely.dir/map.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/map.c.o: ../map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/timely.dir/map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/map.c.o   -c /mnt/dev/c/timely-lang/map.c

CMakeFiles/timely.dir/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/map.c > CMakeFiles/timely.dir/map.c.i

CMakeFiles/timely.dir/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/map.c -o CMakeFiles/timely.dir/map.c.s

CMakeFiles/timely.dir/envir.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/envir.c.o: ../envir.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/timely.dir/envir.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/envir.c.o   -c /mnt/dev/c/timely-lang/envir.c

CMakeFiles/timely.dir/envir.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/envir.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/envir.c > CMakeFiles/timely.dir/envir.c.i

CMakeFiles/timely.dir/envir.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/envir.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/envir.c -o CMakeFiles/timely.dir/envir.c.s

CMakeFiles/timely.dir/tio.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/tio.c.o: ../tio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/timely.dir/tio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/tio.c.o   -c /mnt/dev/c/timely-lang/tio.c

CMakeFiles/timely.dir/tio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/tio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/tio.c > CMakeFiles/timely.dir/tio.c.i

CMakeFiles/timely.dir/tio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/tio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/tio.c -o CMakeFiles/timely.dir/tio.c.s

CMakeFiles/timely.dir/tstring.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/tstring.c.o: ../tstring.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/timely.dir/tstring.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/tstring.c.o   -c /mnt/dev/c/timely-lang/tstring.c

CMakeFiles/timely.dir/tstring.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/tstring.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/tstring.c > CMakeFiles/timely.dir/tstring.c.i

CMakeFiles/timely.dir/tstring.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/tstring.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/tstring.c -o CMakeFiles/timely.dir/tstring.c.s

CMakeFiles/timely.dir/stack.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/stack.c.o: ../stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/timely.dir/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/stack.c.o   -c /mnt/dev/c/timely-lang/stack.c

CMakeFiles/timely.dir/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/stack.c > CMakeFiles/timely.dir/stack.c.i

CMakeFiles/timely.dir/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/stack.c -o CMakeFiles/timely.dir/stack.c.s

CMakeFiles/timely.dir/parser.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/timely.dir/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/parser.c.o   -c /mnt/dev/c/timely-lang/parser.c

CMakeFiles/timely.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/parser.c > CMakeFiles/timely.dir/parser.c.i

CMakeFiles/timely.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/parser.c -o CMakeFiles/timely.dir/parser.c.s

CMakeFiles/timely.dir/tmath.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/tmath.c.o: ../tmath.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/timely.dir/tmath.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/tmath.c.o   -c /mnt/dev/c/timely-lang/tmath.c

CMakeFiles/timely.dir/tmath.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/tmath.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/tmath.c > CMakeFiles/timely.dir/tmath.c.i

CMakeFiles/timely.dir/tmath.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/tmath.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/tmath.c -o CMakeFiles/timely.dir/tmath.c.s

CMakeFiles/timely.dir/log.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/log.c.o: ../log.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/timely.dir/log.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/log.c.o   -c /mnt/dev/c/timely-lang/log.c

CMakeFiles/timely.dir/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/log.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/log.c > CMakeFiles/timely.dir/log.c.i

CMakeFiles/timely.dir/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/log.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/log.c -o CMakeFiles/timely.dir/log.c.s

CMakeFiles/timely.dir/eval.c.o: CMakeFiles/timely.dir/flags.make
CMakeFiles/timely.dir/eval.c.o: ../eval.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/timely.dir/eval.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/timely.dir/eval.c.o   -c /mnt/dev/c/timely-lang/eval.c

CMakeFiles/timely.dir/eval.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/timely.dir/eval.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/dev/c/timely-lang/eval.c > CMakeFiles/timely.dir/eval.c.i

CMakeFiles/timely.dir/eval.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/timely.dir/eval.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/dev/c/timely-lang/eval.c -o CMakeFiles/timely.dir/eval.c.s

# Object files for target timely
timely_OBJECTS = \
"CMakeFiles/timely.dir/main.c.o" \
"CMakeFiles/timely.dir/lexer.c.o" \
"CMakeFiles/timely.dir/list.c.o" \
"CMakeFiles/timely.dir/basic.c.o" \
"CMakeFiles/timely.dir/tree.c.o" \
"CMakeFiles/timely.dir/map.c.o" \
"CMakeFiles/timely.dir/envir.c.o" \
"CMakeFiles/timely.dir/tio.c.o" \
"CMakeFiles/timely.dir/tstring.c.o" \
"CMakeFiles/timely.dir/stack.c.o" \
"CMakeFiles/timely.dir/parser.c.o" \
"CMakeFiles/timely.dir/tmath.c.o" \
"CMakeFiles/timely.dir/log.c.o" \
"CMakeFiles/timely.dir/eval.c.o"

# External object files for target timely
timely_EXTERNAL_OBJECTS =

timely: CMakeFiles/timely.dir/main.c.o
timely: CMakeFiles/timely.dir/lexer.c.o
timely: CMakeFiles/timely.dir/list.c.o
timely: CMakeFiles/timely.dir/basic.c.o
timely: CMakeFiles/timely.dir/tree.c.o
timely: CMakeFiles/timely.dir/map.c.o
timely: CMakeFiles/timely.dir/envir.c.o
timely: CMakeFiles/timely.dir/tio.c.o
timely: CMakeFiles/timely.dir/tstring.c.o
timely: CMakeFiles/timely.dir/stack.c.o
timely: CMakeFiles/timely.dir/parser.c.o
timely: CMakeFiles/timely.dir/tmath.c.o
timely: CMakeFiles/timely.dir/log.c.o
timely: CMakeFiles/timely.dir/eval.c.o
timely: CMakeFiles/timely.dir/build.make
timely: CMakeFiles/timely.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking C executable timely"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timely.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/timely.dir/build: timely

.PHONY : CMakeFiles/timely.dir/build

CMakeFiles/timely.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/timely.dir/cmake_clean.cmake
.PHONY : CMakeFiles/timely.dir/clean

CMakeFiles/timely.dir/depend:
	cd /mnt/dev/c/timely-lang/cmake-build-debug-windows && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/dev/c/timely-lang /mnt/dev/c/timely-lang /mnt/dev/c/timely-lang/cmake-build-debug-windows /mnt/dev/c/timely-lang/cmake-build-debug-windows /mnt/dev/c/timely-lang/cmake-build-debug-windows/CMakeFiles/timely.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/timely.dir/depend

