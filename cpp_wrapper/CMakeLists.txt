cmake_minimum_required(VERSION 3.15)
project(lab2)

add_executable(cmp ../compare_efficiency/cmp.cpp CString.h CString.cpp ../cstring/include/library.h ../cstring/src/library.c)