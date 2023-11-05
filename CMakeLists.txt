cmake_minimum_required(VERSION 3.13)

set(TOOLCHAIN_PREFIX riscv-none-embed)
include(CH573/CMakeLists.txt)

# export compiler command for dev
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project Name
# default to generate target <Project Name>.elf
project(CH573App)

add_definitions(-DDEBUG=1)

set(SOURCES
  ./src/main.c
)

add_executable(${PROJECT_NAME}.elf
  ${SOURCES}
  ${CH573_SOURCES}
)

# Generate hex and link map
add_link_options(-Wl,-Map,${PROJECT_NAME}.map)
add_custom_command(
  TARGET ${PROJECT_NAME}.elf
  BYPRODUCTS ${PROJECT_NAME}.hex ${PROJECT_NAME}.map ${PROJECT_NAME}.lst
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJDUMP} --source --all-headers --demangle --line-numbers --wide ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst
  COMMAND ${CMAKE_SIZE} --format=berkery ${PROJECT_NAME}.elf
  DEPENDS ${PROJECT_NAME}.elf
)
