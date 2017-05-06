cmake_minimum_required(VERSION 3.7)
project(littleShell)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(littleShell ${SOURCE_FILES})