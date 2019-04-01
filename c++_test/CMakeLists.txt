#cmake_mininum_required (VERSION 2.8)

project (run CXX)

set(CXX_FLAGS
    -g
    -Wall
    -std=c++11
    -D_PTHREADS
    #-Wno-unused-parameter
)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#add source file cycle
#aux_source_directory(. DIR_SRCS)

#add_subdirectory()

add_executable(run vector.cpp)

