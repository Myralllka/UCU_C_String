cmake_minimum_required(VERSION 3.15)
project(Lab_C_String C)

# PVS Studio
#include(PVS-Studio.cmake)
#SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(LIB_NAME c_string)
SET(EXEC_NAME main)
SET(TEST_NAME test)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/lib)


set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)

## compilation mode: release OR debug
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)


if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()


#add_library(${LIB_NAME} STATIC src/my_str.c)
add_library(${LIB_NAME} SHARED lib/src/c_string.c lib/include/c_string.h)
#target_link_directories(${LIB_NAME} PUBLIC include)

add_executable(${TEST_NAME} tests/test.c tests/test.h)
target_link_libraries(${TEST_NAME} ${LIB_NAME})

add_executable(${TEST_NAME}_check tests/c_check/test.c)
target_link_libraries(${TEST_NAME}_check ${LIB_NAME} check)

add_executable(${EXEC_NAME} main.c)
target_link_libraries(${EXEC_NAME} ${LIB_NAME})

include(${CMAKE_CURRENT_SOURCE_DIR}/compare_efficiency/CMakeLists.txt)

#####################################
## create own target for library
#pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
#        ANALYZE ${EXEC_NAME} ${LIB_NAME} ${TEST_NAME} ${TEST_NAME}_check
#        OUTPUT FORMAT errorfile
#        MODE GA:1,2,3 OP:1,2,3 GA:1,2,3 OP:1,2,3 64:1,2,3 CS:1,2,3 MISRA:1,2,3
#        LOG target_${PROJECT_NAME}.err)

#####################################
