cmake_minimum_required(VERSION 3.16)
project(BigAdd C)

set(CMAKE_C_STANDARD 99)

add_executable(BigAdd main.c fileio.c word.c identifier.c blocks.c keyword.c variable.c lxanalyzer.c parser.c str.c errhandle.c)