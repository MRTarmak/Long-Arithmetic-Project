cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

project(LongArithmetic)

add_subdirectory("BFNumLib")

include_directories(BFNumLib/include BFNumLib/src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE BFNumLib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)