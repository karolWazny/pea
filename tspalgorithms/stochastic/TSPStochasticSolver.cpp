#include "TSPStochasticSolver.h"

void TSPStochasticSolver::calculateCurrentCost() {
    currentCost = input->getDistance(0, state[0]);
    for(size_t i = 0; i < state.getLength() - 1; i++){
        currentCost += input->getDistance(state[i], state[i + 1]);
    }
    currentCost += input->getDistance(state[state.getLength() - 1], 0);
}

TSPSolution TSPStochasticSolver::buildSolution() {
    TSPSolution solution;
    solution.totalCost = bestCost;
    solution.circuit.pushBack(0);
    for(size_t i = 0; i < bestFound.getLength(); i++){
        solution.circuit.pushBack(bestFound[i]);
    }
    solution.circuit.pushBack(0);
    return solution;
}
