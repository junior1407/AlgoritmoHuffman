cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c inc/huff.h src/huff.c inc/tabela.h src/tabela.c inc/binary.h src/binary.c RedBlack/main.c)
add_executable(untitled ${SOURCE_FILES})