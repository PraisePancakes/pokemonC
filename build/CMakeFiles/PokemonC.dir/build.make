# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\aryas\Downloads\cmake-3.28.0-rc5-windows-x86_64\cmake-3.28.0-rc5-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\aryas\Downloads\cmake-3.28.0-rc5-windows-x86_64\cmake-3.28.0-rc5-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\aryas\OneDrive\Desktop\PokeC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\aryas\OneDrive\Desktop\PokeC\build

# Include any dependencies generated for this target.
include CMakeFiles/PokemonC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PokemonC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PokemonC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PokemonC.dir/flags.make

CMakeFiles/PokemonC.dir/src/main.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/main.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/main.c
CMakeFiles/PokemonC.dir/src/main.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PokemonC.dir/src/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/main.c.obj -MF CMakeFiles\PokemonC.dir\src\main.c.obj.d -o CMakeFiles\PokemonC.dir\src\main.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\main.c

CMakeFiles/PokemonC.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\main.c > CMakeFiles\PokemonC.dir\src\main.c.i

CMakeFiles/PokemonC.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\main.c -o CMakeFiles\PokemonC.dir\src\main.c.s

CMakeFiles/PokemonC.dir/src/ball.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/ball.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/ball.c
CMakeFiles/PokemonC.dir/src/ball.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PokemonC.dir/src/ball.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/ball.c.obj -MF CMakeFiles\PokemonC.dir\src\ball.c.obj.d -o CMakeFiles\PokemonC.dir\src\ball.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\ball.c

CMakeFiles/PokemonC.dir/src/ball.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/ball.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\ball.c > CMakeFiles\PokemonC.dir\src\ball.c.i

CMakeFiles/PokemonC.dir/src/ball.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/ball.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\ball.c -o CMakeFiles\PokemonC.dir\src\ball.c.s

CMakeFiles/PokemonC.dir/src/file.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/file.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/file.c
CMakeFiles/PokemonC.dir/src/file.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/PokemonC.dir/src/file.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/file.c.obj -MF CMakeFiles\PokemonC.dir\src\file.c.obj.d -o CMakeFiles\PokemonC.dir\src\file.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\file.c

CMakeFiles/PokemonC.dir/src/file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/file.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\file.c > CMakeFiles\PokemonC.dir\src\file.c.i

CMakeFiles/PokemonC.dir/src/file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/file.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\file.c -o CMakeFiles\PokemonC.dir\src\file.c.s

CMakeFiles/PokemonC.dir/src/gui.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/gui.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/gui.c
CMakeFiles/PokemonC.dir/src/gui.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/PokemonC.dir/src/gui.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/gui.c.obj -MF CMakeFiles\PokemonC.dir\src\gui.c.obj.d -o CMakeFiles\PokemonC.dir\src\gui.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\gui.c

CMakeFiles/PokemonC.dir/src/gui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/gui.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\gui.c > CMakeFiles\PokemonC.dir\src\gui.c.i

CMakeFiles/PokemonC.dir/src/gui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/gui.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\gui.c -o CMakeFiles\PokemonC.dir\src\gui.c.s

CMakeFiles/PokemonC.dir/src/player.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/player.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/player.c
CMakeFiles/PokemonC.dir/src/player.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/PokemonC.dir/src/player.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/player.c.obj -MF CMakeFiles\PokemonC.dir\src\player.c.obj.d -o CMakeFiles\PokemonC.dir\src\player.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\player.c

CMakeFiles/PokemonC.dir/src/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/player.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\player.c > CMakeFiles\PokemonC.dir\src\player.c.i

CMakeFiles/PokemonC.dir/src/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/player.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\player.c -o CMakeFiles\PokemonC.dir\src\player.c.s

CMakeFiles/PokemonC.dir/src/pokemon.c.obj: CMakeFiles/PokemonC.dir/flags.make
CMakeFiles/PokemonC.dir/src/pokemon.c.obj: C:/Users/aryas/OneDrive/Desktop/PokeC/src/pokemon.c
CMakeFiles/PokemonC.dir/src/pokemon.c.obj: CMakeFiles/PokemonC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/PokemonC.dir/src/pokemon.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PokemonC.dir/src/pokemon.c.obj -MF CMakeFiles\PokemonC.dir\src\pokemon.c.obj.d -o CMakeFiles\PokemonC.dir\src\pokemon.c.obj -c C:\Users\aryas\OneDrive\Desktop\PokeC\src\pokemon.c

CMakeFiles/PokemonC.dir/src/pokemon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/PokemonC.dir/src/pokemon.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aryas\OneDrive\Desktop\PokeC\src\pokemon.c > CMakeFiles\PokemonC.dir\src\pokemon.c.i

CMakeFiles/PokemonC.dir/src/pokemon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/PokemonC.dir/src/pokemon.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aryas\OneDrive\Desktop\PokeC\src\pokemon.c -o CMakeFiles\PokemonC.dir\src\pokemon.c.s

# Object files for target PokemonC
PokemonC_OBJECTS = \
"CMakeFiles/PokemonC.dir/src/main.c.obj" \
"CMakeFiles/PokemonC.dir/src/ball.c.obj" \
"CMakeFiles/PokemonC.dir/src/file.c.obj" \
"CMakeFiles/PokemonC.dir/src/gui.c.obj" \
"CMakeFiles/PokemonC.dir/src/player.c.obj" \
"CMakeFiles/PokemonC.dir/src/pokemon.c.obj"

# External object files for target PokemonC
PokemonC_EXTERNAL_OBJECTS =

PokemonC.exe: CMakeFiles/PokemonC.dir/src/main.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/src/ball.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/src/file.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/src/gui.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/src/player.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/src/pokemon.c.obj
PokemonC.exe: CMakeFiles/PokemonC.dir/build.make
PokemonC.exe: CMakeFiles/PokemonC.dir/linkLibs.rsp
PokemonC.exe: CMakeFiles/PokemonC.dir/objects1.rsp
PokemonC.exe: CMakeFiles/PokemonC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable PokemonC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PokemonC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PokemonC.dir/build: PokemonC.exe
.PHONY : CMakeFiles/PokemonC.dir/build

CMakeFiles/PokemonC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PokemonC.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PokemonC.dir/clean

CMakeFiles/PokemonC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\aryas\OneDrive\Desktop\PokeC C:\Users\aryas\OneDrive\Desktop\PokeC C:\Users\aryas\OneDrive\Desktop\PokeC\build C:\Users\aryas\OneDrive\Desktop\PokeC\build C:\Users\aryas\OneDrive\Desktop\PokeC\build\CMakeFiles\PokemonC.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PokemonC.dir/depend

