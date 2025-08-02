# Set project name and version of CMAKE to use
cmake_minimum_required(VERSION 3.23.1)
project(heap VERSION 1.0)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE heap.h)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})