#include "gtest/gtest.h"

#include "../program/TextFileReader.h"
#include "../tspalgorithms/TSPInputMatrix.h"
#include "../tspalgorithms/TSPDynamicProgrammingSolver.h"

TEST(DynamicSuite, GivesCorrectCostForTestFile){
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    ASSERT_EQ(5, output.totalCost);
}

TEST(DynamicSuite, GivesCorrectPathForTestFile){
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    auto iterator = output.circuit.iterator();
    size_t nodes[] = {0, 2, 1, 4, 3, 0};
    int index = 0;
    while(iterator.hasNext()){
    auto node = iterator.next();
    ASSERT_EQ(nodes[index], node);
    index++;
    }
}

TEST(DynamicSuite, GivesCorrectPathLengthForTestFile){
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    auto iterator = output.circuit.iterator();
    ASSERT_EQ(6, output.circuit.getLength());
}