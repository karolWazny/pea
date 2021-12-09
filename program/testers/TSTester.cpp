#include "TSTester.h"
#include "../../tspalgorithms/TSPInputMatrix.h"
#include "../../tspalgorithms/TSPSolution.h"
#include "../../tspalgorithms/stochastic/TSPTabuSearchSolver.h"
#include "../../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"

void TSTester::test() {
    ffarray<TSPInputMatrix> inputMatrices = ffarray<TSPInputMatrix>(7);
    size_t sizes[7] = {4, 6, 8, 10, 12, 15, 20};
    TSPTabuSearchSolver::Parameters parameters[4] = {
            TSPTabuSearchSolver::Parameters(5, 1, 1000),
            TSPTabuSearchSolver::Parameters(15, 1, 1000),
            TSPTabuSearchSolver::Parameters(5, 8, 1000),
            TSPTabuSearchSolver::Parameters(5, 1, 8000)
    };
    ffarray<TSPSolution> solutions = ffarray<TSPSolution>(7);
    TSPDynamicProgrammingSolver dpSolver;
    TSPTabuSearchSolver tabuSearch;
    ffarray<double> meanRelativeErrors = ffarray<double>(7);


    for(int i = 0; i < 7; i++){
        inputMatrices[i] = randomMatrix(sizes[i]);
        solutions[i] = dpSolver.solveFor(inputMatrices[i]);
        meanRelativeErrors[i] = 0;
    }

    for(auto & parameter : parameters){
        std::cout << parameter.parse() << std::endl;
        tabuSearch.setParameters(parameter);

        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 100; j++){
                auto tsResult = tabuSearch.solveFor(inputMatrices[i]);
                double difference = tsResult.totalCost - solutions[i].totalCost;
                double ratio = difference / solutions[i].totalCost;
                meanRelativeErrors[i] += ratio;
            }
            meanRelativeErrors[i] /= 100;
            std::cout << std::to_string(i) << '\t' << std::to_string(meanRelativeErrors[i]) << std::endl;
        }
    }
}
