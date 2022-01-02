#include "gtest/gtest.h"

#include "../tspalgorithms/third/GeneticSolver.h"
#include "../program/file/AtspFileHandler.h"

TEST(GeneticSuite, OutputPathLengthTestReverseMutation){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = GeneticSolver::Builder().withMutationMethod(MutationMethod::REVERSE).build().solveFor(matrix);
    ASSERT_EQ(6, output.circuit.getLength());
    //std::cout << std::to_string(output.totalCost) << std::endl;
}

TEST(GeneticSuite, OutputPathLengthTestRandomMutation){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("testfile.atsp");
    auto matrix = matrixFrom(values);
    auto output = GeneticSolver::Builder().withMutationMethod(MutationMethod::RANDOM).build().solveFor(matrix);
    ASSERT_EQ(6, output.circuit.getLength());
    //std::cout << std::to_string(output.totalCost) << std::endl;
}

TEST(GeneticSuite, BR17TestReverseMutation){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    for(int j = 0; j < 100; j++){
        auto output = GeneticSolver::Builder().withMutationMethod(MutationMethod::REVERSE).build().solveFor(matrix);
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
TEST(GeneticSuite, BR17TestRandomMutation){
    auto reader = AtspFileHandler();
    auto values = reader.fromFile("br17.atsp");
    auto matrix = matrixFrom(values);
    for(int j = 0; j < 100; j++){
        auto output = GeneticSolver::Builder().withMutationMethod(MutationMethod::RANDOM).build().solveFor(matrix);
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
