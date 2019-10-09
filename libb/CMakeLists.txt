cmake_minimum_required(VERSION 3.15)
project(libb C)

set(CMAKE_C_STANDARD 99)

add_library(libb SHARED library.c library.h)