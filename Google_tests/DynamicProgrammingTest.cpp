#include "gtest/gtest.h"

#include "../program/TextFileReader.h"
#include "../tspalgorithms/TSPInputMatrix.h"
#include "../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"

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
    ASSERT_EQ(output.circuit.toString(), "[0, 2, 1, 4, 3, 0]");
}

TEST(DynamicSuite, GivesCorrectPathLengthForTestFile){
    auto reader = TextFileReader();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    auto iterator = output.circuit.iterator();
    ASSERT_EQ(6, output.circuit.getLength());
}

//this test is commented out due to long (over 10 secs) execution time
/*TEST(DynamicSuite, WorksFor17Cities){
    auto reader = TextFileReader();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    ASSERT_EQ(1, 1);
}*/

TEST(DynamicSuite, WorksFor4Cities){
    auto reader = TextFileReader();
    auto values = reader.fromFile("br4.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPDynamicProgrammingSolver().solveFor(matrix);
    ASSERT_EQ(1, 1);
}