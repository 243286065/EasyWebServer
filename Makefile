# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

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
CMAKE_SOURCE_DIR = /home/lab401/workspace/EasyWebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lab401/workspace/EasyWebServer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lab401/workspace/EasyWebServer/CMakeFiles /home/lab401/workspace/EasyWebServer/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lab401/workspace/EasyWebServer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named EasyWebServer

# Build rule for target.
EasyWebServer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 EasyWebServer
.PHONY : EasyWebServer

# fast build rule for target.
EasyWebServer/fast:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/build
.PHONY : EasyWebServer/fast

src/easyweb.o: src/easyweb.cpp.o
.PHONY : src/easyweb.o

# target to build an object file
src/easyweb.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/easyweb.cpp.o
.PHONY : src/easyweb.cpp.o

src/easyweb.i: src/easyweb.cpp.i
.PHONY : src/easyweb.i

# target to preprocess a source file
src/easyweb.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/easyweb.cpp.i
.PHONY : src/easyweb.cpp.i

src/easyweb.s: src/easyweb.cpp.s
.PHONY : src/easyweb.s

# target to generate assembly for a file
src/easyweb.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/easyweb.cpp.s
.PHONY : src/easyweb.cpp.s

src/ew_epoll.o: src/ew_epoll.cpp.o
.PHONY : src/ew_epoll.o

# target to build an object file
src/ew_epoll.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_epoll.cpp.o
.PHONY : src/ew_epoll.cpp.o

src/ew_epoll.i: src/ew_epoll.cpp.i
.PHONY : src/ew_epoll.i

# target to preprocess a source file
src/ew_epoll.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_epoll.cpp.i
.PHONY : src/ew_epoll.cpp.i

src/ew_epoll.s: src/ew_epoll.cpp.s
.PHONY : src/ew_epoll.s

# target to generate assembly for a file
src/ew_epoll.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_epoll.cpp.s
.PHONY : src/ew_epoll.cpp.s

src/ew_getopt_util.o: src/ew_getopt_util.cpp.o
.PHONY : src/ew_getopt_util.o

# target to build an object file
src/ew_getopt_util.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_getopt_util.cpp.o
.PHONY : src/ew_getopt_util.cpp.o

src/ew_getopt_util.i: src/ew_getopt_util.cpp.i
.PHONY : src/ew_getopt_util.i

# target to preprocess a source file
src/ew_getopt_util.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_getopt_util.cpp.i
.PHONY : src/ew_getopt_util.cpp.i

src/ew_getopt_util.s: src/ew_getopt_util.cpp.s
.PHONY : src/ew_getopt_util.s

# target to generate assembly for a file
src/ew_getopt_util.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_getopt_util.cpp.s
.PHONY : src/ew_getopt_util.cpp.s

src/ew_http_util.o: src/ew_http_util.cpp.o
.PHONY : src/ew_http_util.o

# target to build an object file
src/ew_http_util.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_http_util.cpp.o
.PHONY : src/ew_http_util.cpp.o

src/ew_http_util.i: src/ew_http_util.cpp.i
.PHONY : src/ew_http_util.i

# target to preprocess a source file
src/ew_http_util.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_http_util.cpp.i
.PHONY : src/ew_http_util.cpp.i

src/ew_http_util.s: src/ew_http_util.cpp.s
.PHONY : src/ew_http_util.s

# target to generate assembly for a file
src/ew_http_util.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_http_util.cpp.s
.PHONY : src/ew_http_util.cpp.s

src/ew_init_config_class.o: src/ew_init_config_class.cpp.o
.PHONY : src/ew_init_config_class.o

# target to build an object file
src/ew_init_config_class.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_init_config_class.cpp.o
.PHONY : src/ew_init_config_class.cpp.o

src/ew_init_config_class.i: src/ew_init_config_class.cpp.i
.PHONY : src/ew_init_config_class.i

# target to preprocess a source file
src/ew_init_config_class.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_init_config_class.cpp.i
.PHONY : src/ew_init_config_class.cpp.i

src/ew_init_config_class.s: src/ew_init_config_class.cpp.s
.PHONY : src/ew_init_config_class.s

# target to generate assembly for a file
src/ew_init_config_class.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_init_config_class.cpp.s
.PHONY : src/ew_init_config_class.cpp.s

src/ew_mime_type.o: src/ew_mime_type.cpp.o
.PHONY : src/ew_mime_type.o

# target to build an object file
src/ew_mime_type.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_mime_type.cpp.o
.PHONY : src/ew_mime_type.cpp.o

src/ew_mime_type.i: src/ew_mime_type.cpp.i
.PHONY : src/ew_mime_type.i

# target to preprocess a source file
src/ew_mime_type.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_mime_type.cpp.i
.PHONY : src/ew_mime_type.cpp.i

src/ew_mime_type.s: src/ew_mime_type.cpp.s
.PHONY : src/ew_mime_type.s

# target to generate assembly for a file
src/ew_mime_type.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/ew_mime_type.cpp.s
.PHONY : src/ew_mime_type.cpp.s

src/log.o: src/log.cpp.o
.PHONY : src/log.o

# target to build an object file
src/log.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/log.cpp.o
.PHONY : src/log.cpp.o

src/log.i: src/log.cpp.i
.PHONY : src/log.i

# target to preprocess a source file
src/log.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/log.cpp.i
.PHONY : src/log.cpp.i

src/log.s: src/log.cpp.s
.PHONY : src/log.s

# target to generate assembly for a file
src/log.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/log.cpp.s
.PHONY : src/log.cpp.s

src/util.o: src/util.cpp.o
.PHONY : src/util.o

# target to build an object file
src/util.cpp.o:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/util.cpp.o
.PHONY : src/util.cpp.o

src/util.i: src/util.cpp.i
.PHONY : src/util.i

# target to preprocess a source file
src/util.cpp.i:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/util.cpp.i
.PHONY : src/util.cpp.i

src/util.s: src/util.cpp.s
.PHONY : src/util.s

# target to generate assembly for a file
src/util.cpp.s:
	$(MAKE) -f CMakeFiles/EasyWebServer.dir/build.make CMakeFiles/EasyWebServer.dir/src/util.cpp.s
.PHONY : src/util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... EasyWebServer"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/easyweb.o"
	@echo "... src/easyweb.i"
	@echo "... src/easyweb.s"
	@echo "... src/ew_epoll.o"
	@echo "... src/ew_epoll.i"
	@echo "... src/ew_epoll.s"
	@echo "... src/ew_getopt_util.o"
	@echo "... src/ew_getopt_util.i"
	@echo "... src/ew_getopt_util.s"
	@echo "... src/ew_http_util.o"
	@echo "... src/ew_http_util.i"
	@echo "... src/ew_http_util.s"
	@echo "... src/ew_init_config_class.o"
	@echo "... src/ew_init_config_class.i"
	@echo "... src/ew_init_config_class.s"
	@echo "... src/ew_mime_type.o"
	@echo "... src/ew_mime_type.i"
	@echo "... src/ew_mime_type.s"
	@echo "... src/log.o"
	@echo "... src/log.i"
	@echo "... src/log.s"
	@echo "... src/util.o"
	@echo "... src/util.i"
	@echo "... src/util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
