#include "TSPSimulatedAnnealingSolver.h"
#include "mathfunctions.h"

TSPSolution TSPSimulatedAnnealingSolver::solveFor(const TSPInputMatrix &matrix) {
    prepareMembers(matrix);
    while(keepGoing()){
        break;
    }
    return {};
}

void TSPSimulatedAnnealingSolver::prepareMembers(const TSPInputMatrix &matrix) {
    input = &matrix;
    currentIteration = 0;
    currentTemp = startTemp;
    state = ffarray<int>(input->size() - 1);
    for(size_t i = 0; i < state.getLength(); i++){
        state[i] = i + 1;
    }
    math::fisherYatesShuffle(state);
    bestFound = state.copy();
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
