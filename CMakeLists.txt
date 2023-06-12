cmake_minimum_required(VERSION 3.25)
project(network C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib) #动态库
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib) #静态库

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(buffer)
add_subdirectory(grace)