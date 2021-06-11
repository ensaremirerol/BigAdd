cmake_minimum_required(VERSION 3.16)
project(BigAdd C)

set(CMAKE_C_STANDARD 99)

add_executable(BigAdd src/main.c src/File_IO/fileio.c src/Word/word.c src/IdentifierKeeper/identifier.c src/Blocks/blocks.c src/KeyWord/keyword.c src/VariableStack/variable.c src/LexicalAnalyzer/lxanalyzer.c src/Parser/parser.c src/String/str.c src/ErrorHandle/errhandle.c)