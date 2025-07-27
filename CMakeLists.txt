cmake_minimum_required(VERSION 3.31)
project(ChipDecode C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS -Wall)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(ChipDecode src/main.c
        src/filehelpers.c
        include/filehelpers.h
        src/decoder.c
        include/decoder.h)