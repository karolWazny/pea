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

long long TSPStochasticSolver::costAfterSwapping(size_t index1, size_t index2) {
    if(index1 > index2)
        std::swap(index1, index2);

    long long cost = currentCost;
    long long deltaCost{};
    size_t preElement, postElement;
    if(!index1){
        preElement = 0;
    } else {
        preElement = state[index1 - 1];
    }

    deltaCost -= input->getDistance(preElement, state[index1]);
    deltaCost += input->getDistance(preElement, state[index2]);

    deltaCost -= input->getDistance(state[index1], state[index1 + 1]);
    deltaCost += input->getDistance(state[index2], state[index1 + 1]);

    deltaCost -= input->getDistance(state[index2 - 1], state[index2]);
    deltaCost += input->getDistance(state[index2 - 1], state[index1]);

    if(index2 == state.getLength() - 1) {
        postElement = 0;
    } else {
        postElement = state[index2 + 1];
    }

    deltaCost -= input->getDistance(state[index2], postElement);
    deltaCost += input->getDistance(state[index1], postElement);

    if(index2 == index1 + 1){
        deltaCost += input->getDistance(state[index1], state[index2]);
        deltaCost += input->getDistance(state[index2], state[index1]);
    }
    return cost + deltaCost;
}
