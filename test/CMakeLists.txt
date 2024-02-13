add_executable(tests test.cpp)

add_custom_target(start_test COMMAND test)

target_link_libraries(tests PRIVATE gtest_main BFNumLib)

target_include_directories(tests PRIVATE
        "${PROJECT_SOURCE_DIR}/lib"
)