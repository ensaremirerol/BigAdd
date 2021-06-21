cmake_minimum_required(VERSION 3.16)
project(BigAdd C)

set(CMAKE_C_STANDARD 99)

include_directories("${PROJECT_SOURCE_DIR}/include/Blocks")
include_directories("${PROJECT_SOURCE_DIR}/include/ErrorHandle")
include_directories("${PROJECT_SOURCE_DIR}/include/File_IO")
include_directories("${PROJECT_SOURCE_DIR}/include/IdentifierKeeper")
include_directories("${PROJECT_SOURCE_DIR}/include/KeyWord")
include_directories("${PROJECT_SOURCE_DIR}/include/LexicalAnalyzer")
include_directories("${PROJECT_SOURCE_DIR}/include/Parser")
include_directories("${PROJECT_SOURCE_DIR}/include/String")
include_directories("${PROJECT_SOURCE_DIR}/include/VariableStack")
include_directories("${PROJECT_SOURCE_DIR}/include/Word")
include_directories("${PROJECT_SOURCE_DIR}/include/BigInt")


file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(BigAdd ${src})