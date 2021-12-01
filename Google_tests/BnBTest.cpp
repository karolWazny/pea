#include "gtest/gtest.h"

#include "../program/file/AtspFileHandler.h"
#include "../tspalgorithms/TSPInputMatrix.h"
#include "../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"

TEST(BnBSuite, GivesCorrectCostForTestFile){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPBranchNBoundSolver().solveFor(matrix);
    ASSERT_EQ(5, output.totalCost);
}

TEST(BnBSuite, GivesCorrectPathForTestFile){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPBranchNBoundSolver().solveFor(matrix);
    auto iterator = output.circuit.iterator();
    size_t nodes[] = {0, 2, 1, 4, 3, 0};
    int index = 0;
    while(iterator.hasNext()){
        auto node = iterator.next();
        ASSERT_EQ(nodes[index], node);
        index++;
    }
}

TEST(BnBSuite, GivesCorrectPathLengthForTestFile){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPBranchNBoundSolver().solveFor(matrix);
    auto iterator = output.circuit.iterator();
    ASSERT_EQ(6, output.circuit.getLength());
}
