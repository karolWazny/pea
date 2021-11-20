#include "gtest/gtest.h"

#include "../tspalgorithms/TSPSimulatedAnnealingSolver.h"
#include "../program/TextFileReader.h"

TEST(SASuite, OutputPathLengthTest){
    TSPSimulatedAnnealingSolver solver;
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPSimulatedAnnealingSolver().solveFor(matrix);
    ASSERT_EQ(6, output.circuit.getLength());
}
