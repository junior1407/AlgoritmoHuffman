cmake_minimum_required(VERSION 3.7)
project(RedBlack)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/redblack.c inc/redblack.h main.c)
add_executable(RedBlack ${SOURCE_FILES})