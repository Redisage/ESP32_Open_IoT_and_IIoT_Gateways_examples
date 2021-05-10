file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "flash_project_args"
  "hello-world.bin"
  "hello-world.map"
  "project_elf_src.c"
  "CMakeFiles/hello-world.elf.dir/project_elf_src.c.obj"
  "hello-world.elf"
  "hello-world.elf.manifest"
  "hello-world.elf.pdb"
  "project_elf_src.c"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/hello-world.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
