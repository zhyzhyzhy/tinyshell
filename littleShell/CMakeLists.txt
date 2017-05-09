cmake_minimum_required(VERSION 3.7)
project(littleShell)

set(CMAKE_C_STANDARD 99)


set(SOURCE_FILES main.c line_parser.c line_parser.h  buildin.c buildin.h env.c env.h util.c util.h process.c process.h)
add_executable(littleShell ${SOURCE_FILES})