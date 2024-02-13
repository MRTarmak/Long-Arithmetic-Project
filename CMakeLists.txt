cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

project(LongArithmetic)

add_subdirectory("lib")
add_subdirectory("test")

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE BFNumLib)

target_include_directories(main PUBLIC
        "${PROJECT_SOURCE_DIR}/lib"
)