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
CMAKE_COMMAND = /home/josh/clion-2020.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/josh/clion-2020.2.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/josh/CLionProjects/RISC_V_VM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/josh/CLionProjects/RISC_V_VM/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/riscvVM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/riscvVM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/riscvVM.dir/flags.make

CMakeFiles/riscvVM.dir/main.c.o: CMakeFiles/riscvVM.dir/flags.make
CMakeFiles/riscvVM.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/josh/CLionProjects/RISC_V_VM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/riscvVM.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/riscvVM.dir/main.c.o   -c /home/josh/CLionProjects/RISC_V_VM/main.c

CMakeFiles/riscvVM.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/riscvVM.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/josh/CLionProjects/RISC_V_VM/main.c > CMakeFiles/riscvVM.dir/main.c.i

CMakeFiles/riscvVM.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/riscvVM.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/josh/CLionProjects/RISC_V_VM/main.c -o CMakeFiles/riscvVM.dir/main.c.s

CMakeFiles/riscvVM.dir/elfhandler.c.o: CMakeFiles/riscvVM.dir/flags.make
CMakeFiles/riscvVM.dir/elfhandler.c.o: ../elfhandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/josh/CLionProjects/RISC_V_VM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/riscvVM.dir/elfhandler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/riscvVM.dir/elfhandler.c.o   -c /home/josh/CLionProjects/RISC_V_VM/elfhandler.c

CMakeFiles/riscvVM.dir/elfhandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/riscvVM.dir/elfhandler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/josh/CLionProjects/RISC_V_VM/elfhandler.c > CMakeFiles/riscvVM.dir/elfhandler.c.i

CMakeFiles/riscvVM.dir/elfhandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/riscvVM.dir/elfhandler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/josh/CLionProjects/RISC_V_VM/elfhandler.c -o CMakeFiles/riscvVM.dir/elfhandler.c.s

# Object files for target riscvVM
riscvVM_OBJECTS = \
"CMakeFiles/riscvVM.dir/main.c.o" \
"CMakeFiles/riscvVM.dir/elfhandler.c.o"

# External object files for target riscvVM
riscvVM_EXTERNAL_OBJECTS =

riscvVM: CMakeFiles/riscvVM.dir/main.c.o
riscvVM: CMakeFiles/riscvVM.dir/elfhandler.c.o
riscvVM: CMakeFiles/riscvVM.dir/build.make
riscvVM: CMakeFiles/riscvVM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/josh/CLionProjects/RISC_V_VM/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable riscvVM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/riscvVM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/riscvVM.dir/build: riscvVM

.PHONY : CMakeFiles/riscvVM.dir/build

CMakeFiles/riscvVM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/riscvVM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/riscvVM.dir/clean

CMakeFiles/riscvVM.dir/depend:
	cd /home/josh/CLionProjects/RISC_V_VM/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/josh/CLionProjects/RISC_V_VM /home/josh/CLionProjects/RISC_V_VM /home/josh/CLionProjects/RISC_V_VM/cmake-build-debug /home/josh/CLionProjects/RISC_V_VM/cmake-build-debug /home/josh/CLionProjects/RISC_V_VM/cmake-build-debug/CMakeFiles/riscvVM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/riscvVM.dir/depend

