#include "gtest/gtest.h"

#include "../tspalgorithms/TSPTabuSearchSolver.h"
#include "../program/TextFileReader.h"

TEST(TSSuite, OutputPathLengthTest){
    TSPTabuSearchSolver solver;
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = solver.solveFor(matrix);
    ASSERT_EQ(6, output.circuit.getLength());
}
