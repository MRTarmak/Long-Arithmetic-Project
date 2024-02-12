cmake_minimum_required(VERSION 3.22)
project(LongArithmeticProject)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        bfnumlib.hpp
)

set(SOURCE_FILES
        bfnumlib.cpp
)

add_library(BFNumLib STATIC lib/bfnumlib.cpp
        main.cpp
)