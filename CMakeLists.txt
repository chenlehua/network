cmake_minimum_required(VERSION 3.25)
project(network C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib) #动态库
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib) #静态库

include_directories(${PROJECT_SOURCE_DIR})

include(CheckSymbolExists)
check_symbol_exists(epoll_create "sys/epoll.h" EPOLL_EXISTS)
if (EPOLL_EXISTS)
    # Linux下设置为epoll
    set(EPOLL_ENABLE 1 CACHE INTERNAL "enable epoll")

    # Linux下也设置为poll
    #    set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
else ()
    set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
endif ()


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/include/config.h)


include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

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
add_subdirectory(poll-multi-reactor)
add_subdirectory(epoll-multi-reactor)
