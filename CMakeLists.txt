cmake_minimum_required(VERSION 3.20)
project(pea)

set(CMAKE_CXX_STANDARD 17)

add_executable(pea main.cpp)

add_subdirectory(Google_tests)
add_subdirectory(tspalgorithms)
add_subdirectory(structure_templates_lib)
add_subdirectory(program)

target_link_libraries(pea tspalgorithms structure_templates_lib program)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()