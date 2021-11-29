cmake_minimum_required(VERSION 3.17)
project(rbtree_lib)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        BRTree.h
        node.h)

set(SOURCE_FILES
        index.cpp
        BRTree.cpp
        node.cpp)

add_library(rbtree_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})