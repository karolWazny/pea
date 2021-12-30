#include "GeneticSolver.h"

#include "../mathfunctions.h"

TSPSolution GeneticSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    TSPSolution solution;
    this->input = &inputMatrix;

    prepareMembers();

    for(int i = 0; i < input->size(); i++){
        solution.circuit.pushBack(i);
    }
    solution.circuit.pushBack(0);
    solution.totalCost = 0;
    auto iterator = solution.circuit.iterator();
    auto second = iterator.next();
    while(iterator.hasNext()){
        auto first = second;
        second = iterator.next();
        solution.totalCost += input->getDistance(first, second);
    }
    return solution;
}

void GeneticSolver::prepareMembers() {
    breed = ffarray<Individual>(parameters.population);
    for(int i = 0; i < breed.getLength(); i++){
        Individual& ind = breed[i];
        for(int j = 0; j < input->size() - 1; j++){
            ind.permutation[j] = j + 1;
        }
        math::fisherYatesShuffle(ind.permutation);
        ind.cost = calculateCost(ind);
    }
}

long long GeneticSolver::calculateCost(const GeneticSolver::Individual &individual) {
    long long output{};
    int second{};
    for(int i = 0; i < individual.permutation.getLength(); i++){
        auto first = second;
        second = individual.permutation[i];
        output += input->getDistance(first, second);
    }
    output += input->getDistance(individual.permutation[individual.permutation.getLength() - 1], 0);
    return output;
}
