# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL

# Include any dependencies generated for this target.
include CMakeFiles/player-test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/player-test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/player-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/player-test.dir/flags.make

CMakeFiles/player-test.dir/unitTests/player-test.cpp.o: CMakeFiles/player-test.dir/flags.make
CMakeFiles/player-test.dir/unitTests/player-test.cpp.o: /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/unitTests/player-test.cpp
CMakeFiles/player-test.dir/unitTests/player-test.cpp.o: CMakeFiles/player-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/player-test.dir/unitTests/player-test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/player-test.dir/unitTests/player-test.cpp.o -MF CMakeFiles/player-test.dir/unitTests/player-test.cpp.o.d -o CMakeFiles/player-test.dir/unitTests/player-test.cpp.o -c /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/unitTests/player-test.cpp

CMakeFiles/player-test.dir/unitTests/player-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/player-test.dir/unitTests/player-test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/unitTests/player-test.cpp > CMakeFiles/player-test.dir/unitTests/player-test.cpp.i

CMakeFiles/player-test.dir/unitTests/player-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/player-test.dir/unitTests/player-test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/unitTests/player-test.cpp -o CMakeFiles/player-test.dir/unitTests/player-test.cpp.s

# Object files for target player-test
player__test_OBJECTS = \
"CMakeFiles/player-test.dir/unitTests/player-test.cpp.o"

# External object files for target player-test
player__test_EXTERNAL_OBJECTS = \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/bElem.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/bElemAttr.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/bElemStats.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/bouba.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/brickCluster.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/bunker.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/chamber.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/chamberArea.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/characterStats.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/configManager.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/door.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/elementFactory.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/explosives.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/floorElement.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/goldenApple.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/inputManager.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/inventory.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/key.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/kiki.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/killableElements.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/levelLoader.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/mechanical.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/monster.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/monsterBrain.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/movableElements.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/nonSteppable.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/patrollingDrone.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/plainGun.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/plainMissile.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/player.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/presenter.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/puppetMasterFR.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/randomLevelGenerator.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/randomWordGen.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/rubbish.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/simpleBomb.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/soundManager.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/stackedElement.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/teleport.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/videoDriver.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/videoElementDef.cpp.o" \
"/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/GardenOfErisLib.dir/src/wall.cpp.o"

player-test: CMakeFiles/player-test.dir/unitTests/player-test.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/bElem.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/bElemAttr.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/bElemStats.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/bouba.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/brickCluster.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/bunker.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/chamber.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/chamberArea.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/characterStats.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/configManager.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/door.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/elementFactory.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/explosives.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/floorElement.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/goldenApple.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/inputManager.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/inventory.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/key.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/kiki.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/killableElements.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/levelLoader.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/mechanical.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/monster.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/monsterBrain.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/movableElements.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/nonSteppable.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/patrollingDrone.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/plainGun.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/plainMissile.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/player.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/presenter.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/puppetMasterFR.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/randomLevelGenerator.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/randomWordGen.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/rubbish.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/simpleBomb.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/soundManager.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/stackedElement.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/teleport.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/videoDriver.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/videoElementDef.cpp.o
player-test: CMakeFiles/GardenOfErisLib.dir/src/wall.cpp.o
player-test: CMakeFiles/player-test.dir/build.make
player-test: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.74.0
player-test: CMakeFiles/player-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable player-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/player-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/player-test.dir/build: player-test
.PHONY : CMakeFiles/player-test.dir/build

CMakeFiles/player-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/player-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/player-test.dir/clean

CMakeFiles/player-test.dir/depend:
	cd /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL /home/c/git/GardenOfErisorOnboxiousLabirynth/Gardens-of-Eris/GoEoOL/CMakeFiles/player-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/player-test.dir/depend

