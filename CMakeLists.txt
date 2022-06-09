cmake_minimum_required(VERSION 3.21)
project(huffman-code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_executable(huffman-code
        main.c
        libs/
        libs/node.h
        libs/node.c
        libs/string.h
        libs/string.c
        )