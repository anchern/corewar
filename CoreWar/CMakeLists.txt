cmake_minimum_required(VERSION 3.12)
project(CoreWar C)

set(CMAKE_C_STANDARD 99)

include_directories(lib/mylib)

#add_definitions("-Wall -Wextra -Werror -O3")

add_executable(corewar src/main.c inc/vm.h inc/op.h)

add_subdirectory(lib/mylib)

target_link_libraries(corewar mylib)