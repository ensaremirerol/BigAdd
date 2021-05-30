cmake_minimum_required(VERSION 3.16)

project(lexical_win C)

set(CMAKE_C_STANDARD 99)

add_executable(lexical_win main.c fileio.h keyword.h linetrckr.h identifier.h blocks.h)
