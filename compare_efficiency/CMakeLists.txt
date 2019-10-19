#[[ A cmakeLists file for building a program for comparing the  efficiency of a built-in library
and this one ]]

cmake_minimum_required(VERSION 3.15)
project(lab2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(comp_eff compare_efficiency/cmp.cpp cpp_wrapper/CString.h cpp_wrapper/CString.cpp lib/include/c_string.h lib/src/c_string.c)
