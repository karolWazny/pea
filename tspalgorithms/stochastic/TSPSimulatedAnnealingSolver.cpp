#include "TSPSimulatedAnnealingSolver.h"
#include "../mathfunctions.h"
#include <cmath>
#include <sstream>

RealRandom<double> TSPSimulatedAnnealingSolver::realRandom = RealRandom<double>(0.0, 1.0);
Randomizer TSPSimulatedAnnealingSolver::intRandom = Randomizer();

TSPSolution TSPSimulatedAnnealingSolver::solveFor(const TSPInputMatrix &matrix) {
    prepareMembers(matrix);
    for(int i = 0; i < getTries(); i++){
        prepareForNextTry();
        while(keepGoing()){
            for(iteration = 0; iteration < getIterations(); iteration++){
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
    candidateCost = costAfterSwapping(firstIndex, secondIndex);
    swapVertices();
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
    currentTemp = getStartTemp();
    math::fisherYatesShuffle(state);
    calculateCurrentCost();
}

void TSPSimulatedAnnealingSolver::setStartTemp(double startTemp) {
    params.setStartTemp(startTemp);
}

void TSPSimulatedAnnealingSolver::setCoolingConstant(double coolingConstant) {
    params.setCoolingConstant(coolingConstant);
}

void TSPSimulatedAnnealingSolver::setIterations(size_t iterations) {
    params.setIterations(iterations);
}

double TSPSimulatedAnnealingSolver::getStartTemp() const {
    return params.getStartTemp();
}

double TSPSimulatedAnnealingSolver::getCoolingConstant() const {
    return params.getCoolingConstant();
}

size_t TSPSimulatedAnnealingSolver::getIterations() const {
    return params.getIterations();
}

void TSPSimulatedAnnealingSolver::setMinimalTemperature(double minimalTemperature) {
    params.setMinimalTemp(minimalTemperature);
}

double TSPSimulatedAnnealingSolver::getMinimalTemperature() const {
    return params.getMinimalTemp();
}

int TSPSimulatedAnnealingSolver::getTries() const {
    return params.getTries();
}

void TSPSimulatedAnnealingSolver::setTries(int tries) {
    params.setTries(tries);
}

TSPSimulatedAnnealingSolver::Parameters TSPSimulatedAnnealingSolver::Parameters::from(const std::string& string) {
    auto stream = std::stringstream(string);
    return from(stream);
}

TSPSimulatedAnnealingSolver::Parameters TSPSimulatedAnnealingSolver::Parameters::from(std::istream &stream) {
    std::string buffer;
    Parameters output;
    while(!stream.eof()){
        stream >> buffer;
        if(buffer == "TRIES")
            stream >> output.tries;
        else if (buffer == "START_TEMP")
            stream >> output.startTemp;
        else if (buffer == "MIN_TEMP")
            stream >> output.minimalTemp;
        else if (buffer == "COOLING_CONST")
            stream >> output.coolingConstant;
        else if (buffer == "ITERATIONS")
            stream >> output.iterations;
        else
            std::getline(stream, buffer);
    }
    return output;
}

std::string TSPSimulatedAnnealingSolver::Parameters::parse() {
    std::stringstream stream;

    stream << "TRIES\t" << std::to_string(tries) << std::endl
            << "START_TEMP\t" << std::to_string(startTemp) << std::endl
            << "MIN_TEMP\t" << std::to_string(minimalTemp) << std::endl
            << "COOLING_CONST\t" << std::to_string(coolingConstant) << std::endl
            << "ITERATIONS\t" << std::to_string(iterations) << std::endl;

    return stream.str();
}

