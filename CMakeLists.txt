cmake_minimum_required(VERSION 4.2)
project(mynote C)

set(CMAKE_C_STANDARD 23)

add_executable(mynote main.c
        paths.h
        paths.c
        storage.h
        storage.c)
