cmake_minimum_required(VERSION 3.31)
project(ChipDecode C)

set(CMAKE_C_STANDARD 23)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(ChipDecode src/main.c
        src/filehelpers.c
        include/filehelpers.h
        src/disassembler.c
        include/disassembler.h)