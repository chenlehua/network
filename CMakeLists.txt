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
add_subdirectory(keepalive)
add_subdirectory(address-used)
add_subdirectory(stream)
add_subdirectory(reliable)
add_subdirectory(ssh)
add_subdirectory(poll)
add_subdirectory(nonblocking)
add_subdirectory(epoll)
add_subdirectory(fork)
add_subdirectory(thread)
add_subdirectory(poll-reactor)