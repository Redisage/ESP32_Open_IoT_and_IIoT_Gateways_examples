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

# Utility rule file for bootloader.

# Include the progress variables for this target.
include CMakeFiles/bootloader.dir/progress.make

CMakeFiles/bootloader: CMakeFiles/bootloader-complete


CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-install
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-mkdir
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-download
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-update
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-patch
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-configure
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-build
CMakeFiles/bootloader-complete: bootloader-prefix/src/bootloader-stamp/bootloader-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'bootloader'"
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/CMakeFiles
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/CMakeFiles/bootloader-complete
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-done

bootloader-prefix/src/bootloader-stamp/bootloader-install: bootloader-prefix/src/bootloader-stamp/bootloader-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'bootloader'"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\bootloader && C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E echo_append
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\bootloader && C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-install

bootloader-prefix/src/bootloader-stamp/bootloader-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'bootloader'"
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/esp-idf/components/bootloader/subproject
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/tmp
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E make_directory C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-mkdir

bootloader-prefix/src/bootloader-stamp/bootloader-download: bootloader-prefix/src/bootloader-stamp/bootloader-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'bootloader'"
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E echo_append
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-download

bootloader-prefix/src/bootloader-stamp/bootloader-update: bootloader-prefix/src/bootloader-stamp/bootloader-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'bootloader'"
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E echo_append
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-update

bootloader-prefix/src/bootloader-stamp/bootloader-patch: bootloader-prefix/src/bootloader-stamp/bootloader-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'bootloader'"
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E echo_append
	C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-patch

bootloader-prefix/src/bootloader-stamp/bootloader-configure: bootloader-prefix/tmp/bootloader-cfgcmd.txt
bootloader-prefix/src/bootloader-stamp/bootloader-configure: bootloader-prefix/src/bootloader-stamp/bootloader-update
bootloader-prefix/src/bootloader-stamp/bootloader-configure: bootloader-prefix/src/bootloader-stamp/bootloader-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'bootloader'"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\bootloader && C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -DSDKCONFIG=C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/sdkconfig -DIDF_PATH=C:/Users/Pawel/Desktop/esp-idf -DIDF_TARGET=esp32 -DPYTHON_DEPS_CHECKED=1 -DPYTHON=python -DEXTRA_COMPONENT_DIRS=C:/Users/Pawel/Desktop/esp-idf/components/bootloader -DLEGACY_INCLUDE_COMMON_HEADERS= "-GCodeBlocks - MinGW Makefiles" C:/Users/Pawel/Desktop/esp-idf/components/bootloader/subproject
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\bootloader && C:\Users\Pawel\.espressif\tools\cmake\3.16.4\bin\cmake.exe -E touch C:/Users/Pawel/Desktop/CGE2/cge2-firmware-examples/LED/CodeB/bootloader-prefix/src/bootloader-stamp/bootloader-configure

bootloader-prefix/src/bootloader-stamp/bootloader-build: bootloader-prefix/src/bootloader-stamp/bootloader-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'bootloader'"
	cd /d C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\bootloader && $(MAKE)

bootloader: CMakeFiles/bootloader
bootloader: CMakeFiles/bootloader-complete
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-install
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-mkdir
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-download
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-update
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-patch
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-configure
bootloader: bootloader-prefix/src/bootloader-stamp/bootloader-build
bootloader: CMakeFiles/bootloader.dir/build.make

.PHONY : bootloader

# Rule to build all files generated by this target.
CMakeFiles/bootloader.dir/build: bootloader

.PHONY : CMakeFiles/bootloader.dir/build

CMakeFiles/bootloader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bootloader.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bootloader.dir/clean

CMakeFiles/bootloader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB C:\Users\Pawel\Desktop\CGE2\cge2-firmware-examples\LED\CodeB\CMakeFiles\bootloader.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bootloader.dir/depend

