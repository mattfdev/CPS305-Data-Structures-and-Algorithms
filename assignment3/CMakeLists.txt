cmake_minimum_required(VERSION 3.3)
project(assignment3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES complete.c trie.c trie.h)
add_executable(assignment3 ${SOURCE_FILES})