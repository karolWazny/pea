#include "TSPSimulatedAnnealingSolver.h"
#include "mathfunctions.h"
#include <cmath>

RealRandom<double> TSPSimulatedAnnealingSolver::realRandom = RealRandom<double>(0.0, 1.0);
Randomizer TSPSimulatedAnnealingSolver::intRandom = Randomizer();

TSPSolution TSPSimulatedAnnealingSolver::solveFor(const TSPInputMatrix &matrix) {
    prepareMembers(matrix);
    for(int i = 0; i < tries; i++){
        prepareForNextTry();
        while(keepGoing()){
            for(currentIteration = 0; currentIteration < iterations; currentIteration++){
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
    recalculateCandidateCost();
    swapVertices();
}

void TSPSimulatedAnnealingSolver::recalculateCandidateCost() {
    candidateCost = currentCost;
    //todo uprościć ładnie ten kod
    if(!index){
        candidateCost -= input->getDistance(0, state[index])
                + input->getDistance(state[index], state[secondIndex])
                + input->getDistance(state[secondIndex], state[postIndex]);

        candidateCost += input->getDistance(0, state[secondIndex])
                + input->getDistance(state[secondIndex], state[index])
                + input->getDistance(state[index], state[postIndex]);
    } else if(!secondIndex){
        candidateCost -= input->getDistance(state[preIndex], state[index])
                + input->getDistance(state[index], 0)
                + input->getDistance(0, state[secondIndex])
                + input->getDistance(state[secondIndex], state[postIndex]);

        candidateCost += input->getDistance(0, state[index])
                + input->getDistance(state[index], state[postIndex])
                + input->getDistance(state[preIndex], state[secondIndex])
                + input->getDistance(state[secondIndex], 0);
    } else if(secondIndex == state.getLength() - 1){
        candidateCost -= input->getDistance(state[preIndex], state[index])
                + input->getDistance(state[index], state[secondIndex])
                + input->getDistance(state[secondIndex], 0);

        candidateCost += input->getDistance(state[preIndex], state[secondIndex])
                + input->getDistance(state[secondIndex], state[index])
                + input->getDistance(state[index], 0);
    } else {
        candidateCost -= input->getDistance(state[preIndex], state[index])
                + input->getDistance(state[index], state[secondIndex])
                + input->getDistance(state[secondIndex], state[postIndex]);

        candidateCost += input->getDistance(state[preIndex], state[secondIndex])
                + input->getDistance(state[secondIndex], state[index])
                + input->getDistance(state[index], state[postIndex]);
    }
}

void TSPSimulatedAnnealingSolver::swapVertices() {
    auto buffer = state[index];
    state[index] = state[secondIndex];
    state[secondIndex] = buffer;
}

void TSPSimulatedAnnealingSolver::calculateIndexesForNextMove() {
    index = intRandom.getULong(state.getLength() - 1);
    secondIndex = (index + 1) % state.getLength();
    preIndex = index == 0 ? state.getLength() - 1 : index - 1;
    postIndex = (index + 2) % state.getLength();
}

TSPSolution TSPSimulatedAnnealingSolver::buildSolution() {
    TSPSolution solution;
    solution.totalCost = bestCost;
    solution.circuit.pushBack(0);
    for(size_t i = 0; i < bestFound.getLength(); i++){
        solution.circuit.pushBack(bestFound[i]);
    }
    solution.circuit.pushBack(0);
    return solution;
}

void TSPSimulatedAnnealingSolver::prepareMembers(const TSPInputMatrix &matrix) {
    input = &matrix;
    state = ffarray<int>(input->size() - 1);
    for(size_t i = 0; i < state.getLength(); i++){
        state[i] = i + 1;
    }
    prepareForNextTry();
    bestCost = candidateCost;
    bestFound = state.copy();
}

void TSPSimulatedAnnealingSolver::prepareForNextTry() {
    currentIteration = 0;
    currentTemp = startTemp;
    math::fisherYatesShuffle(state);
    calculateCandidateCost();
    currentCost = candidateCost;
}

void TSPSimulatedAnnealingSolver::calculateCandidateCost() {
    candidateCost = input->getDistance(0, state[0]);
    for(size_t i = 0; i < state.getLength() - 1; i++){
        candidateCost += input->getDistance(state[i], state[i + 1]);
    }
    candidateCost += input->getDistance(state[state.getLength() - 1], 0);
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

