#include "gtest/gtest.h"

#include "../tspalgorithms/TSPTabuSearchSolver.h"
#include "../program/TextFileReader.h"

TEST(TSSuite, OutputPathLengthTest){
    TSPTabuSearchSolver solver;
    auto reader = TextFileReader();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    //std::cout << std::to_string(matrix.size());
    auto output = solver.solveFor(matrix);
    //ASSERT_EQ(6, output.circuit.getLength());
    std::cout << std::to_string(output.totalCost) << std::endl;
    std::cout << output.circuit.toString() << std::endl;
}
