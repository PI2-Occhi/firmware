# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/firmware/mqtt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/firmware/mqtt/mqtt_build

# Include any dependencies generated for this target.
include src/CMakeFiles/mqtt_client.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mqtt_client.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mqtt_client.dir/flags.make

src/CMakeFiles/mqtt_client.dir/mqtt_client.c.o: src/CMakeFiles/mqtt_client.dir/flags.make
src/CMakeFiles/mqtt_client.dir/mqtt_client.c.o: ../src/mqtt_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/firmware/mqtt/mqtt_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/mqtt_client.dir/mqtt_client.c.o"

src/CMakeFiles/mqtt_client.dir/mqtt_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mqtt_client.dir/mqtt_client.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

src/CMakeFiles/mqtt_client.dir/mqtt_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mqtt_client.dir/mqtt_client.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

# Object files for target mqtt_client
mqtt_client_OBJECTS = \
"CMakeFiles/mqtt_client.dir/mqtt_client.c.o"

# External object files for target mqtt_client
mqtt_client_EXTERNAL_OBJECTS =

src/mqtt_client: src/CMakeFiles/mqtt_client.dir/mqtt_client.c.o
src/mqtt_client: src/CMakeFiles/mqtt_client.dir/build.make
src/mqtt_client: src/CMakeFiles/mqtt_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/firmware/mqtt/mqtt_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library mqtt_client"
	cd /home/pi/firmware/mqtt/mqtt_build/src && $(CMAKE_COMMAND) -P CMakeFiles/mqtt_client.dir/cmake_clean_target.cmake
	cd /home/pi/firmware/mqtt/mqtt_build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mqtt_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mqtt_client.dir/build: src/mqtt_client

.PHONY : src/CMakeFiles/mqtt_client.dir/build

src/CMakeFiles/mqtt_client.dir/clean:
	cd /home/pi/firmware/mqtt/mqtt_build/src && $(CMAKE_COMMAND) -P CMakeFiles/mqtt_client.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mqtt_client.dir/clean

src/CMakeFiles/mqtt_client.dir/depend:
	cd /home/pi/firmware/mqtt/mqtt_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/firmware/mqtt /home/pi/firmware/mqtt/src /home/pi/firmware/mqtt/mqtt_build /home/pi/firmware/mqtt/mqtt_build/src /home/pi/firmware/mqtt/mqtt_build/src/CMakeFiles/mqtt_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mqtt_client.dir/depend

