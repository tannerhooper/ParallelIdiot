cmake_minimum_required(VERSION 3.6)
project(idiot)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(SOURCE_FILES main.cpp)
add_executable(idiot ${SOURCE_FILES})