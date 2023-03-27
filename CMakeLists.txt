cmake_minimum_required(VERSION 3.18)

project(measurement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test-measure test-measure.cpp)
target_link_libraries(test-measure GTest::gtest_main)

add_executable(test-measure-nonauto test-measure-nonauto.cpp)
target_compile_options(test-measure-nonauto PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(test-measure)
