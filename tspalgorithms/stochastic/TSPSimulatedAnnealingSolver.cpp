#include "TSPSimulatedAnnealingSolver.h"
#include "../mathfunctions.h"
#include <cmath>

RealRandom<double> TSPSimulatedAnnealingSolver::realRandom = RealRandom<double>(0.0, 1.0);
Randomizer TSPSimulatedAnnealingSolver::intRandom = Randomizer();

TSPSolution TSPSimulatedAnnealingSolver::solveFor(const TSPInputMatrix &matrix) {
    prepareMembers(matrix);
    for(int i = 0; i < tries; i++){
        prepareForNextTry();
        while(keepGoing()){
            for(iteration = 0; iteration < iterations; iteration++){
                calculateNextCandidateSolution();
                evaluateCandidateSolution();
            }
            updateParameters();
        }
    }
    return buildSolution();
}

void TSPSimulatedAnnealingSolver::evaluateCandidateSolution() {
    if(acceptCandidate()){
        currentCost = candidateCost;
        if(candidateCost < bestCost){
            updateBest();
        }
    } else {
        rollbackSwapVertices();
    }
}

bool TSPSimulatedAnnealingSolver::acceptStochastically() const {
    return realRandom() < probability();
}

void TSPSimulatedAnnealingSolver::calculateNextCandidateSolution() {
    calculateIndexesForNextMove();
    recalculateCandidateCost(firstIndex, secondIndex);
    swapVertices();
}

void TSPSimulatedAnnealingSolver::recalculateCandidateCost(size_t index1, size_t index2) {
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
    candidateCost =  cost + deltaCost;
}

void TSPSimulatedAnnealingSolver::swapVertices() {
    std::swap(state[firstIndex], state[secondIndex]);
}

void TSPSimulatedAnnealingSolver::calculateIndexesForNextMove() {
    firstIndex = intRandom.getULong(state.getLength() - 2);
    secondIndex = firstIndex + intRandom.getULong(state.getLength() - 2 - firstIndex) + 1;
}

void TSPSimulatedAnnealingSolver::prepareMembers(const TSPInputMatrix &matrix) {
    input = &matrix;
    state = ffarray<int>(input->size() - 1);
    for(size_t i = 0; i < state.getLength(); i++){
        state[i] = i + 1;
    }
    prepareForNextTry();
    bestCost = currentCost;
    bestFound = state.copy();
}

void TSPSimulatedAnnealingSolver::prepareForNextTry() {
    iteration = 0;
    currentTemp = startTemp;
    math::fisherYatesShuffle(state);
    calculateCurrentCost();
}

void TSPSimulatedAnnealingSolver::setStartTemp(double startTemp) {
    TSPSimulatedAnnealingSolver::startTemp = startTemp;
}

void TSPSimulatedAnnealingSolver::setCoolingConstant(double coolingConstant) {
    TSPSimulatedAnnealingSolver::coolingConstant = coolingConstant;
}

void TSPSimulatedAnnealingSolver::setIterations(size_t iterations) {
    TSPSimulatedAnnealingSolver::iterations = iterations;
}

double TSPSimulatedAnnealingSolver::getStartTemp() const {
    return startTemp;
}

double TSPSimulatedAnnealingSolver::getCoolingConstant() const {
    return coolingConstant;
}

size_t TSPSimulatedAnnealingSolver::getIterations() const {
    return iterations;
}

void TSPSimulatedAnnealingSolver::setMinimalTemperature(double minimalTemperature) {
    TSPSimulatedAnnealingSolver::minimalTemperature = minimalTemperature;
}

double TSPSimulatedAnnealingSolver::getMinimalTemperature() const {
    return minimalTemperature;
}

