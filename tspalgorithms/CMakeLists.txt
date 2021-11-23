cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        TSPInputMatrix.h
        TSPAbstractSolver.h
        TSPSolution.h
        deterministic/TSPBruteForceSolver.h
        deterministic/TSPDynamicProgrammingSolver.h
        deterministic/TSPBranchNBoundSolver.h
        mathfunctions.h
        PlanarVector.h
        stochastic/TSPTabuSearchSolver.h
        stochastic/TSPSimulatedAnnealingSolver.h
        stochastic/TSPStochasticSolver.h)

set(SOURCE_FILES
        index.cpp
        TSPInputMatrix.cpp
        deterministic/TSPBruteForceSolver.cpp
        deterministic/TSPDynamicProgrammingSolver.cpp
        deterministic/TSPBranchNBoundSolver.cpp
        mathfunctions.cpp
        PlanarVector.cpp
        stochastic/TSPTabuSearchSolver.cpp
        stochastic/TSPSimulatedAnnealingSolver.cpp
        stochastic/TSPStochasticSolver.cpp)

link_libraries(structure_templates_lib)

add_library(tspalgorithms ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()