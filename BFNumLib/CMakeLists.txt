project(BFNumLib)

add_library(BFNumLib src/bfnumlib.cpp include/bfnumlib.hpp)

include_directories(src include test)

add_executable(BFNumTest test/test.cpp)

target_link_libraries(BFNumTest GTest::gtest_main BFNumLib)

include(GoogleTest)
gtest_discover_tests(BFNumTest)