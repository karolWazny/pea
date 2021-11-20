cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        TSPInputMatrix.h
        TSPAbstractSolver.h
        TSPSolution.h
        TSPBruteForceSolver.h
        TSPDynamicProgrammingSolver.h
        TSPBranchNBoundSolver.h
        mathfunctions.h
        PlanarVector.h
        TSPTabuSearchSolver.h
        TSPSimulatedAnnealingSolver.h)

set(SOURCE_FILES
        index.cpp
        TSPInputMatrix.cpp
        TSPBruteForceSolver.cpp
        TSPDynamicProgrammingSolver.cpp
        TSPBranchNBoundSolver.cpp
        mathfunctions.cpp
        PlanarVector.cpp
        TSPTabuSearchSolver.cpp
        TSPSimulatedAnnealingSolver.cpp)

link_libraries(structure_templates_lib)

add_library(tspalgorithms ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()