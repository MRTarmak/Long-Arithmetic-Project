cmake_minimum_required(VERSION 3.22)
project(LongArithmeticProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_library(BFNumLib lib/bfnumlib.cpp)

target_link_libraries(main PUBLIC BFNumLib)