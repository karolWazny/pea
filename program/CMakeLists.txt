cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        Main.h
        Operations.h
        Randomizer.h
        file/AtspFileHandler.h
        StopWatch.h
        testers/TimeMeasurer.h)

set(SOURCE_FILES
        Main.cpp
        Operations.cpp
        Randomizer.cpp
        file/AtspFileHandler.cpp
        StopWatch.cpp
        testers/TimeMeasurer.cpp ProgramSetup.cpp ProgramSetup.h Program.cpp Program.h PeaSetup.cpp PeaSetup.h RealRandom.cpp RealRandom.h file/TxtFileHandler.cpp file/TxtFileHandler.h file/FileHandler.cpp file/FileHandler.h testers/SATester.cpp testers/SATester.h testers/TSTester.cpp testers/TSTester.h)

link_libraries(tspalgorithms)

add_library(program ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()