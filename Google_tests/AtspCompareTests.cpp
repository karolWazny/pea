#include "gtest/gtest.h"
#include "../tspalgorithms/atsp.h"

/*
TEST(CompareSuite, giveSameOutputForSameInputWithBrute){
    for(int i = 4; i <= 12; i++){
        for(int j = 0; j < 8; j++){
            auto inputMatrix = randomMatrix(i);
            auto bruteSolution = TSPBruteForceSolver().solveFor(inputMatrix);
            auto dynamicSolution = TSPDynamicProgrammingSolver().solveFor(inputMatrix);
            auto bnbSolution = TSPBranchNBoundSolver().solveFor(inputMatrix);

            if(!(dynamicSolution.totalCost == bruteSolution.totalCost && dynamicSolution.totalCost == bnbSolution.totalCost)){
                std::cout << "Size: " << std::to_string(i) << ", iteration: " << std::to_string(j + 1) << std::endl;
                std::cout << "Brute:   " << bruteSolution.circuit.toString() << ", cost: " << std::to_string(bruteSolution.totalCost) << std::endl;
                std::cout << "Dynamic: " << dynamicSolution.circuit.toString() << ", cost: " << std::to_string(dynamicSolution.totalCost) << std::endl;
                std::cout << "BnB:     " << bnbSolution.circuit.toString() << ", cost: " << std::to_string(bnbSolution.totalCost) << std::endl;
                std::cout << inputMatrix.representation() << std::endl;
            }



            ASSERT_EQ(bruteSolution.totalCost, dynamicSolution.totalCost);
            ASSERT_EQ(bruteSolution.totalCost, bnbSolution.totalCost);
            ASSERT_EQ(dynamicSolution.totalCost, bnbSolution.totalCost);
        }
    }
}

TEST(CompareSuite, giveSameOutputForSameInputMediumInstance){
    for(int i = 13; i <= 17; i++){
        for(int j = 0; j < 1; j++){
            auto inputMatrix = randomMatrix(i);
            auto dynamicSolution = TSPDynamicProgrammingSolver().solveFor(inputMatrix);
            auto bnbSolution = TSPBranchNBoundSolver().solveFor(inputMatrix);

            if(dynamicSolution.totalCost != bnbSolution.totalCost){
                std::cout << "Size: " << std::to_string(i) << ", iteration: " << std::to_string(j + 1) << std::endl;
                std::cout << "Dynamic: " << dynamicSolution.circuit.toString() << ", cost: " << std::to_string(dynamicSolution.totalCost) << std::endl;
                std::cout << "BnB:     " << bnbSolution.circuit.toString() << ", cost: " << std::to_string(bnbSolution.totalCost) << std::endl;
                std::cout << inputMatrix.representation() << std::endl;
            }

            ASSERT_EQ(dynamicSolution.totalCost, bnbSolution.totalCost);
        }
    }
}*/
