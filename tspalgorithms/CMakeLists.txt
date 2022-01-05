cmake_minimum_required(VERSION 3.17)
project(pea)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES
        TSPInputMatrix.h
        TSPAbstractSolver.h
        TSPSolution.h
        deterministic/TSPBruteForceSolver.h
        deterministic/TSPDynamicProgrammingSolver.h
        deterministic/TSPBranchNBoundSolver.h
        ../utils/mathfunctions.h
        ../utils/PlanarVector.h
        stochastic/TSPTabuSearchSolver.h
        stochastic/TSPSimulatedAnnealingSolver.h
        stochastic/TSPStochasticSolver.h)

set(SOURCE_FILES
        index.cpp
        TSPInputMatrix.cpp
        deterministic/TSPBruteForceSolver.cpp
        deterministic/TSPDynamicProgrammingSolver.cpp
        deterministic/TSPBranchNBoundSolver.cpp
        ../utils/mathfunctions.cpp
        ../utils/PlanarVector.cpp
        stochastic/TSPTabuSearchSolver.cpp
        stochastic/TSPSimulatedAnnealingSolver.cpp
        stochastic/TSPStochasticSolver.cpp third/GeneticSolver.cpp third/GeneticSolver.h third/Individual.cpp third/Individual.h third/Mutation.h third/Mutation.cpp)

link_libraries(structure_templates_lib)

add_library(tspalgorithms ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()