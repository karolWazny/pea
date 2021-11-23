#include "TSPTabuSearchSolver.h"
#include "../mathfunctions.h"

TSPSolution TSPTabuSearchSolver::solveFor(const TSPInputMatrix &matrix) {
    prepareMembers(matrix);
    runAlgorithm();
    return buildSolution();
}

void TSPTabuSearchSolver::prepareMembers(const TSPInputMatrix &matrix) {
    input = &matrix;
    state = ffarray<int>(input->size() - 1);
    for(size_t i = 0; i < state.getLength(); i++){
        state[i] = i + 1;
    }
    tabu = ffarray<ffarray<long long>>(input->size() - 2);
    for(size_t i = 0; i < tabu.getLength(); i++){
        tabu[i] = ffarray<long long>(tabu.getLength() - i);
        for(size_t j = 0; j < tabu[i].getLength(); j++){
            tabu[i][j] = 0;
        }
    }
    math::fisherYatesShuffle(state);

    calculateCurrentCost();
    bestCost = currentCost;
}

void TSPTabuSearchSolver::runAlgorithm() {
    for(iteration = 0; iteration < 1000; iteration++){
        candidateCost = INT64_MAX;
        foundNewBest = false;

        for(size_t j = 0; j < tabu.getLength(); j++){
            for(size_t k = 0; k < tabu[j].getLength(); k++){
                evaluateSwapping(j, j + k + 1);
            }
        }

        updateMembers();
    }
}

void TSPTabuSearchSolver::evaluateSwapping(size_t index1, size_t index2) {
    auto potentialCost = candidateSolution(index1, index2);
    bool aspirates = satisfiesAspiration(potentialCost, index1, index2);
    if(aspirates){
        firstIndex = index1;
        secondIndex = index2;
        candidateCost = potentialCost;
        foundNewBest = true;
    } else if (isNotTabu(index1, index2) && isPossiblyBetter(potentialCost)){
        firstIndex = index1;
        secondIndex = index2;
        candidateCost = potentialCost;
    }
}

long long TSPTabuSearchSolver::candidateSolution(size_t index1, size_t index2) const {
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

void TSPTabuSearchSolver::updateMembers() {
    if(candidateCost != INT64_MAX){
        auto buffer = state[firstIndex];
        state[firstIndex] = state[secondIndex];
        state[secondIndex] = buffer;
        currentCost = candidateCost;
        tabu[firstIndex][secondIndex - firstIndex - 1] = iteration;
    }

    if(foundNewBest){
        bestFound = state.copy();
        bestCost = currentCost;
    }
}
