cmake_minimum_required(VERSION 3.12)
project(CoreWar C)

set(CMAKE_C_STANDARD 99)

include_directories(lib/mylib)

#add_definitions("-Wall -Wextra -Werror -O3")


add_executable(corewar src/main.c inc/vm.h inc/op.h src/commands/commands1-5.c src/commands/commands6-10.c src/commands/commands11-15.c src/iobytes.c src/read_options/read_options1.c src/additional_function.c src/read_options/read_options2.c src/read_options/for_read_options.c)

add_subdirectory(lib/mylib)

target_link_libraries(corewar mylib)