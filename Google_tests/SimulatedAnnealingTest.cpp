#include "gtest/gtest.h"

#include "../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"
#include "../program/file/AtspFileHandler.h"

TEST(SASuite, OutputPathLengthTest){
    TSPSimulatedAnnealingSolver solver;
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = TSPSimulatedAnnealingSolver().solveFor(matrix);
    ASSERT_EQ(6, output.circuit.getLength());
    std::cout << std::to_string(output.totalCost) << std::endl;
}

TEST(SASuite, BR17Test){
    TSPSimulatedAnnealingSolver solver;
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    for(int j = 0; j < 100; j++){
        auto output = TSPSimulatedAnnealingSolver(5000000, 0.999, 10000, 20, 8).solveFor(matrix);
        for(int i = 0; i < 17; i++){
            ASSERT_TRUE(output.circuit.contains(i));
        }
        ASSERT_EQ(0, output.circuit.get(0));
        ASSERT_EQ(0, output.circuit.getLast());
        size_t cost{};
        for(int i = 0; i < output.circuit.getLength() - 1; i++){
            cost += matrix.getDistance(output.circuit.get(i), output.circuit.get(i + 1));
        }
        ASSERT_EQ(output.totalCost, cost);
        //std::cout << std::to_string(output.totalCost) << std::endl;
    }
}