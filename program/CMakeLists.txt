cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Main.h
        Operations.h
        Randomizer.h
        TextFileReader.h
        StopWatch.h
        TimeMeasurer.h)

set(SOURCE_FILES
        Main.cpp
        Operations.cpp
        Randomizer.cpp
        TextFileReader.cpp
        StopWatch.cpp
        TimeMeasurer.cpp ProgramSetup.cpp ProgramSetup.h Program.cpp Program.h PeaSetup.cpp PeaSetup.h RealRandom.cpp RealRandom.h)

link_libraries(tspalgorithms)

add_library(program ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()