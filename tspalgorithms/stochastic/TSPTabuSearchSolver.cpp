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
    auto potentialCost = costAfterSwapping(index1, index2);
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
