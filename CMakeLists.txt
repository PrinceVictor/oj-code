project(cplusplus)
cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )
set(SRC_LIST
    problem1001
#    leetcode
#    char_sequence_permutation
    )
add_executable(${PROJECT_NAME} ${SRC_LIST})
