cmake_minimum_required(VERSION 3.6)
project(heap)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c heap/heap.c)
add_executable(heap ${SOURCE_FILES})

target_link_libraries(heap m)
