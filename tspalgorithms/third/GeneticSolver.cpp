#include "GeneticSolver.h"

#include "../mathfunctions.h"

RealRandom<double> GeneticSolver::random = RealRandom(0.0);

TSPSolution GeneticSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    TSPSolution solution;
    this->input = &inputMatrix;

    prepareMembers();


    for(int i = 0; i < 100; i++){
        assessPopulation();
        createNewBreed();
        applyCrossoverToBreed();
        applyMutationToBreed();
        setBreedAsParents();
    }



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
    population = ffarray<Individual>(parameters.population);
    for(int i = 0; i < breed.getLength(); i++){
        Individual& ind = breed[i];
        for(int j = 0; j < input->size() - 1; j++){
            ind.permutation[j] = j + 1;
        }
        math::fisherYatesShuffle(ind.permutation);
    }
}

long long GeneticSolver::calculateCost(const Individual &individual) {
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

Individual GeneticSolver::chooseTournamentStyle() {
    long long cost{INT64_MAX};
    long long currentWinnerIndex{};
    Randomizer rand;
    for(int i = 0; i < 8; i++){
        auto index = rand.getULong(population.getLength());
        if(population[index].cost < cost){
            cost = population[index].cost;
            currentWinnerIndex = index;
        }
    }
    return population[currentWinnerIndex];
}

void GeneticSolver::applyMutationToBreed() {
    for(int i = 0; i < breed.getLength(); i++){
        if(random() < parameters.mutationProbability)
            mutate(breed[i]);
    }
}

void GeneticSolver::applyCrossoverToBreed() {
    math::fisherYatesShuffle(breed);
    for(int i = 1; i < breed.getLength(); i += 2){
        if(random() < parameters.crossoverProbability)
            crossover(breed[i], breed[i - 1]);
    }
}

void GeneticSolver::createNewBreed() {

}

void GeneticSolver::crossover(Individual &, Individual &) {

}

void GeneticSolver::assessPopulation() {
    for(int i = 0; i < population.getLength(); i++){
        population[i].cost = calculateCost(population[i]);
        if(population[i].cost <= currentlyBest.cost) {
            currentlyBest.cost = population[i].cost;
            currentlyBest.permutation = population[i].permutation.copy();
        }
    }
}

void GeneticSolver::setBreedAsParents() {
    population = breed;
}
