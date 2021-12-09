#include "SATester.h"
#include "../../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"
#include "../../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"

void SATester::test() {
    ffarray<TSPInputMatrix> inputMatrices = ffarray<TSPInputMatrix>(7);
    size_t sizes[7] = {4, 6, 8, 10, 12, 15, 20};
    TSPSimulatedAnnealingSolver::Parameters parameters[6] = {
            TSPSimulatedAnnealingSolver::Parameters(5000, 0.8, 20, 50, 1),
            TSPSimulatedAnnealingSolver::Parameters(15000, 0.8, 20, 50, 1),
            TSPSimulatedAnnealingSolver::Parameters(5000, 0.999, 20, 50, 1),
            TSPSimulatedAnnealingSolver::Parameters(5000, 0.8, 200, 50, 1),
            TSPSimulatedAnnealingSolver::Parameters(5000, 0.8, 20, 5, 1),
            TSPSimulatedAnnealingSolver::Parameters(5000, 0.8, 20, 50, 8)
    };
    ffarray<TSPSolution> solutions = ffarray<TSPSolution>(7);
    TSPDynamicProgrammingSolver dpSolver;
    TSPSimulatedAnnealingSolver saSolver(5000, 0.999, 20, 50, 1);
    ffarray<double> meanRelativeErrors = ffarray<double>(7);


    for(int i = 0; i < 7; i++){
        inputMatrices[i] = randomMatrix(sizes[i]);
        solutions[i] = dpSolver.solveFor(inputMatrices[i]);
        meanRelativeErrors[i] = 0;
    }

    for(auto & parameter : parameters){
        std::cout << parameter.parse() << std::endl;
        saSolver.setParameters(parameter);

        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 100; j++){
                auto saResult = saSolver.solveFor(inputMatrices[i]);
                double difference = saResult.totalCost - solutions[i].totalCost;
                double ratio = difference / solutions[i].totalCost;
                meanRelativeErrors[i] += ratio;
            }
            meanRelativeErrors[i] /= 100;
            std::cout << std::to_string(i) << '\t' << std::to_string(meanRelativeErrors[i]) << std::endl;
        }
    }
}
