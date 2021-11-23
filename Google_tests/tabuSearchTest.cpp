#include "gtest/gtest.h"

#include "../tspalgorithms/stochastic/TSPTabuSearchSolver.h"
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
    //std::cout << output.circuit.toString() << std::endl;
}

TEST(TSSuite, BR17Test){
    TSPTabuSearchSolver solver;
    auto reader = TextFileReader();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    for(int j = 0; j < 100; j++){
        auto output = TSPTabuSearchSolver().solveFor(matrix);
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
    }
}
