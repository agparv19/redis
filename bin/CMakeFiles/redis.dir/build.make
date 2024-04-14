# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/agparv19/codemill/redis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/agparv19/codemill/redis/bin

# Include any dependencies generated for this target.
include CMakeFiles/redis.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/redis.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/redis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/redis.dir/flags.make

CMakeFiles/redis.dir/server.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/server.cpp.o: ../server.cpp
CMakeFiles/redis.dir/server.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/redis.dir/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/server.cpp.o -MF CMakeFiles/redis.dir/server.cpp.o.d -o CMakeFiles/redis.dir/server.cpp.o -c /home/agparv19/codemill/redis/server.cpp

CMakeFiles/redis.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/server.cpp > CMakeFiles/redis.dir/server.cpp.i

CMakeFiles/redis.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/server.cpp -o CMakeFiles/redis.dir/server.cpp.s

CMakeFiles/redis.dir/type.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/type.cpp.o: ../type.cpp
CMakeFiles/redis.dir/type.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/redis.dir/type.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/type.cpp.o -MF CMakeFiles/redis.dir/type.cpp.o.d -o CMakeFiles/redis.dir/type.cpp.o -c /home/agparv19/codemill/redis/type.cpp

CMakeFiles/redis.dir/type.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/type.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/type.cpp > CMakeFiles/redis.dir/type.cpp.i

CMakeFiles/redis.dir/type.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/type.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/type.cpp -o CMakeFiles/redis.dir/type.cpp.s

CMakeFiles/redis.dir/RESPParser.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/RESPParser.cpp.o: ../RESPParser.cpp
CMakeFiles/redis.dir/RESPParser.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/redis.dir/RESPParser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/RESPParser.cpp.o -MF CMakeFiles/redis.dir/RESPParser.cpp.o.d -o CMakeFiles/redis.dir/RESPParser.cpp.o -c /home/agparv19/codemill/redis/RESPParser.cpp

CMakeFiles/redis.dir/RESPParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/RESPParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/RESPParser.cpp > CMakeFiles/redis.dir/RESPParser.cpp.i

CMakeFiles/redis.dir/RESPParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/RESPParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/RESPParser.cpp -o CMakeFiles/redis.dir/RESPParser.cpp.s

CMakeFiles/redis.dir/redisstore.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/redisstore.cpp.o: ../redisstore.cpp
CMakeFiles/redis.dir/redisstore.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/redis.dir/redisstore.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/redisstore.cpp.o -MF CMakeFiles/redis.dir/redisstore.cpp.o.d -o CMakeFiles/redis.dir/redisstore.cpp.o -c /home/agparv19/codemill/redis/redisstore.cpp

CMakeFiles/redis.dir/redisstore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/redisstore.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/redisstore.cpp > CMakeFiles/redis.dir/redisstore.cpp.i

CMakeFiles/redis.dir/redisstore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/redisstore.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/redisstore.cpp -o CMakeFiles/redis.dir/redisstore.cpp.s

CMakeFiles/redis.dir/common.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/common.cpp.o: ../common.cpp
CMakeFiles/redis.dir/common.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/redis.dir/common.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/common.cpp.o -MF CMakeFiles/redis.dir/common.cpp.o.d -o CMakeFiles/redis.dir/common.cpp.o -c /home/agparv19/codemill/redis/common.cpp

CMakeFiles/redis.dir/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/common.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/common.cpp > CMakeFiles/redis.dir/common.cpp.i

CMakeFiles/redis.dir/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/common.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/common.cpp -o CMakeFiles/redis.dir/common.cpp.s

CMakeFiles/redis.dir/cmds.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/cmds.cpp.o: ../cmds.cpp
CMakeFiles/redis.dir/cmds.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/redis.dir/cmds.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/cmds.cpp.o -MF CMakeFiles/redis.dir/cmds.cpp.o.d -o CMakeFiles/redis.dir/cmds.cpp.o -c /home/agparv19/codemill/redis/cmds.cpp

CMakeFiles/redis.dir/cmds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/cmds.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/cmds.cpp > CMakeFiles/redis.dir/cmds.cpp.i

CMakeFiles/redis.dir/cmds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/cmds.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/cmds.cpp -o CMakeFiles/redis.dir/cmds.cpp.s

CMakeFiles/redis.dir/config.cpp.o: CMakeFiles/redis.dir/flags.make
CMakeFiles/redis.dir/config.cpp.o: ../config.cpp
CMakeFiles/redis.dir/config.cpp.o: CMakeFiles/redis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/redis.dir/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/redis.dir/config.cpp.o -MF CMakeFiles/redis.dir/config.cpp.o.d -o CMakeFiles/redis.dir/config.cpp.o -c /home/agparv19/codemill/redis/config.cpp

CMakeFiles/redis.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/redis.dir/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agparv19/codemill/redis/config.cpp > CMakeFiles/redis.dir/config.cpp.i

CMakeFiles/redis.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/redis.dir/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agparv19/codemill/redis/config.cpp -o CMakeFiles/redis.dir/config.cpp.s

# Object files for target redis
redis_OBJECTS = \
"CMakeFiles/redis.dir/server.cpp.o" \
"CMakeFiles/redis.dir/type.cpp.o" \
"CMakeFiles/redis.dir/RESPParser.cpp.o" \
"CMakeFiles/redis.dir/redisstore.cpp.o" \
"CMakeFiles/redis.dir/common.cpp.o" \
"CMakeFiles/redis.dir/cmds.cpp.o" \
"CMakeFiles/redis.dir/config.cpp.o"

# External object files for target redis
redis_EXTERNAL_OBJECTS =

redis: CMakeFiles/redis.dir/server.cpp.o
redis: CMakeFiles/redis.dir/type.cpp.o
redis: CMakeFiles/redis.dir/RESPParser.cpp.o
redis: CMakeFiles/redis.dir/redisstore.cpp.o
redis: CMakeFiles/redis.dir/common.cpp.o
redis: CMakeFiles/redis.dir/cmds.cpp.o
redis: CMakeFiles/redis.dir/config.cpp.o
redis: CMakeFiles/redis.dir/build.make
redis: CMakeFiles/redis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/agparv19/codemill/redis/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable redis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/redis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/redis.dir/build: redis
.PHONY : CMakeFiles/redis.dir/build

CMakeFiles/redis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/redis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/redis.dir/clean

CMakeFiles/redis.dir/depend:
	cd /home/agparv19/codemill/redis/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agparv19/codemill/redis /home/agparv19/codemill/redis /home/agparv19/codemill/redis/bin /home/agparv19/codemill/redis/bin /home/agparv19/codemill/redis/bin/CMakeFiles/redis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/redis.dir/depend
