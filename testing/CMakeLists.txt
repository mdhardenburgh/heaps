cmake_minimum_required(VERSION 3.23.1)

project(heapTest VERSION 1.0.0  LANGUAGES CXX)
add_executable(${PROJECT_NAME} heapTest.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -c -g -std=c++17 -Wall -W -Werror -pedantic)
target_include_directories(${PROJECT_NAME} PUBLIC . ../)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    gtest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
FetchContent_MakeAvailable(gtest)
enable_testing()

target_link_libraries(${PROJECT_NAME} heap gtest gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}
    PROPERTIES
    LABELS "unit"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)