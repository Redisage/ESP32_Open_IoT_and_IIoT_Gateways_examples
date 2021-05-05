file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "flash_project_args"
  "project_elf_src.c"
  "wifi_client.bin"
  "wifi_client.map"
  "CMakeFiles/wifi_client.elf.dir/project_elf_src.c.obj"
  "project_elf_src.c"
  "wifi_client.elf"
  "wifi_client.elf.manifest"
  "wifi_client.elf.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/wifi_client.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
