# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB

# Include any dependencies generated for this target.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend.make

# Include the progress variables for this target.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/flags.make

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/flags.make
esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj: C:/Users/Pawel/Desktop/esp-idf/components/tcpip_adapter/tcpip_adapter_compat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && C:\Users\Pawel\.espressif\tools\xtensa-esp32-elf\esp-2020r3-8.4.0\xtensa-esp32-elf\bin\xtensa-esp32-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\__idf_tcpip_adapter.dir\tcpip_adapter_compat.c.obj   -c C:\Users\Pawel\Desktop\esp-idf\components\tcpip_adapter\tcpip_adapter_compat.c

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.i"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && C:\Users\Pawel\.espressif\tools\xtensa-esp32-elf\esp-2020r3-8.4.0\xtensa-esp32-elf\bin\xtensa-esp32-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Pawel\Desktop\esp-idf\components\tcpip_adapter\tcpip_adapter_compat.c > CMakeFiles\__idf_tcpip_adapter.dir\tcpip_adapter_compat.c.i

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.s"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && C:\Users\Pawel\.espressif\tools\xtensa-esp32-elf\esp-2020r3-8.4.0\xtensa-esp32-elf\bin\xtensa-esp32-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Pawel\Desktop\esp-idf\components\tcpip_adapter\tcpip_adapter_compat.c -o CMakeFiles\__idf_tcpip_adapter.dir\tcpip_adapter_compat.c.s

# Object files for target __idf_tcpip_adapter
__idf_tcpip_adapter_OBJECTS = \
"CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj"

# External object files for target __idf_tcpip_adapter
__idf_tcpip_adapter_EXTERNAL_OBJECTS =

esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj
esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build.make
esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtcpip_adapter.a"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && $(CMAKE_COMMAND) -P CMakeFiles\__idf_tcpip_adapter.dir\cmake_clean_target.cmake
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\__idf_tcpip_adapter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build: esp-idf/tcpip_adapter/libtcpip_adapter.a

.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/clean:
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter && $(CMAKE_COMMAND) -P CMakeFiles\__idf_tcpip_adapter.dir\cmake_clean.cmake
.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/clean

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED C:\Users\Pawel\Desktop\esp-idf\components\tcpip_adapter C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\esp-idf\tcpip_adapter\CMakeFiles\__idf_tcpip_adapter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend

