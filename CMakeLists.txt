cmake_minimum_required(VERSION 3.19)
project(BigAdd C)

set(CMAKE_C_STANDARD 99)

add_executable(BigAdd main.c fileio.c fileio.h word.c word.h identifier.c identifier.h blocks.c keyword.c keyword.h variable.c variable.h lxanalyzer.c lxanalyzer.h parser.c parser.h)