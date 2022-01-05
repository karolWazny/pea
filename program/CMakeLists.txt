cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        Main.h
        Operations.h
        ../utils/Randomizer.h
        file/AtspFileHandler.h
        ../utils/StopWatch.h
        measurements/TimeMeasurer.h)

set(SOURCE_FILES
        Main.cpp
        Operations.cpp
        ../utils/Randomizer.cpp
        file/AtspFileHandler.cpp
        ../utils/StopWatch.cpp
        measurements/TimeMeasurer.cpp ProgramSetup.cpp ProgramSetup.h Program.cpp Program.h PeaSetup.cpp PeaSetup.h ../utils/RealRandom.cpp ../utils/RealRandom.h file/TxtFileHandler.cpp file/TxtFileHandler.h file/FileHandler.cpp file/FileHandler.h measurements/GAMeasurements.cpp measurements/GAMeasurements.h ../utils/display.h ../utils/display.cpp)

link_libraries(tspalgorithms)

add_library(program ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()