#include "GeneticSolver.h"

TSPSolution GeneticSolver::solveFor(const TSPInputMatrix &input) {
    TSPSolution solution;
    for(int i = 0; i < input.size(); i++){
        solution.circuit.pushBack(i);
    }
    solution.circuit.pushBack(0);
    solution.totalCost = 0;
    auto iterator = solution.circuit.iterator();
    auto second = iterator.next();
    while(iterator.hasNext()){
        auto first = second;
        second = iterator.next();
        solution.totalCost += input.getDistance(first, second);
    }
    return solution;
}
