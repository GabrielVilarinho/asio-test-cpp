cmake_minimum_required(VERSION 3.23)

project(PROJ2)

#set(CPP_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE -pthread")

add_subdirectory(include)
add_subdirectory(src)