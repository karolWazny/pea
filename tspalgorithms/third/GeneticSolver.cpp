#include "GeneticSolver.h"

#include "../mathfunctions.h"
#include "../../structure_templates_lib/rbtree_lib/BRTree.h"

RealRandom<double> GeneticSolver::random = RealRandom(0.0);
Randomizer GeneticSolver::intRandom = Randomizer();

TSPSolution GeneticSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    this->input = &inputMatrix;

    prepareMembers();

    for(int i = 0; i < parameters.generations; i++){
        assessPopulation();
        createNewBreed();
        applyCrossoverToBreed();
        applyMutationToBreed();
        setBreedAsParents();
    }
    return buildSolutionFromBest();
}

void GeneticSolver::prepareMembers() {
    population = ffarray<Individual>(parameters.population);
    for(int i = 0; i < population.getLength(); i++){
        Individual& ind = population[i];
        ind.permutation = ffarray<int>(input->size() - 1);
        for(int j = 0; j < ind.permutation.getLength(); j++){
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
    for(int i = 0; i < 12; i++){
        auto index = rand.getULong(population.getLength() - 1);
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
    breed = ffarray<Individual>(parameters.population);
    for(int i = 0; i < breed.getLength(); i++){
        breed[i] = chooseTournamentStyle();
    }
}

void GeneticSolver::crossover(Individual &first, Individual &second) {
    auto firstIndex = intRandom.getInt(first.permutation.getLength() - 1);
    auto secondIndex = intRandom.getInt(first.permutation.getLength() - 1);
    if(firstIndex > secondIndex)
        std::swap(firstIndex, secondIndex);
    Individual child1 = produceChild(first, second, firstIndex, secondIndex);
    Individual child2 = produceChild(second, first, firstIndex, secondIndex);
    first = child1;
    second = child2;
}

Individual GeneticSolver::produceChild(Individual &first, Individual &second, int firstCrossingPoint, int secondCrossingPoint) {
    if(firstCrossingPoint > secondCrossingPoint)
        std::swap(firstCrossingPoint, secondCrossingPoint);
    Individual child;
    child.permutation = ffarray<int>(first.permutation.getLength());
    BRTree elementsFromFirst;
    BRTree indexesUsed;
    for(auto i = firstCrossingPoint; i <= secondCrossingPoint; i++){
        child.permutation[i] = first.permutation[i];
        elementsFromFirst.put(first.permutation[i]);
        indexesUsed.put(i);
    }
    for(auto i = firstCrossingPoint; i <= secondCrossingPoint; i++){
        if(!elementsFromFirst.contains(second.permutation[i])){
            auto analogousElementFromFirst = first.permutation[i];
            do{
                auto indexInSecondParent = second.permutation.indexOf(analogousElementFromFirst);
                if(indexInSecondParent < firstCrossingPoint or indexInSecondParent > secondCrossingPoint){
#if DEBUG
                    std::cout << "DEBUG(GeneticSolver::crossover): Index: " << std::to_string(indexInSecondParent) << ", value: " << std::to_string(analogousElementFromFirst) << std::endl;
#endif
                    indexesUsed.put(indexInSecondParent);
                    child.permutation[indexInSecondParent] = second.permutation[i];
                    break;
                }
                analogousElementFromFirst = first.permutation[indexInSecondParent];
            }while(true);
        }
    }
    for(int i = 0; i < firstCrossingPoint; i++){
        if(elementsFromFirst.contains(second.permutation[i]))
            continue;
        auto positionToPutAt = i;
        while(indexesUsed.contains(positionToPutAt))
            positionToPutAt++;
        indexesUsed.put(positionToPutAt);
        child.permutation[positionToPutAt] = second.permutation[i];
    }

    for(int i = secondCrossingPoint + 1; i < child.permutation.getLength(); i++){
        if(elementsFromFirst.contains(second.permutation[i]))
            continue;
        auto positionToPutAt = i;
        while(indexesUsed.contains(positionToPutAt))
            positionToPutAt++;
        indexesUsed.put(positionToPutAt);
        child.permutation[positionToPutAt] = second.permutation[i];
    }
    return child;
}

void GeneticSolver::assessPopulation() {
    for(int i = 0; i < population.getLength(); i++){
        population[i].cost = calculateCost(population[i]);
        if(population[i].cost < currentlyBest.cost) {
            currentlyBest.cost = population[i].cost;
            currentlyBest.permutation = population[i].permutation.copy();
        }
    }
}

void GeneticSolver::setBreedAsParents() {
    population = breed;
}

TSPSolution GeneticSolver::buildSolutionFromBest() const {
    TSPSolution solution;
    solution.circuit.pushBack(0);
    for(int i = 0; i < currentlyBest.permutation.getLength(); i++){
        solution.circuit.pushBack(currentlyBest.permutation[i]);
    }
    solution.circuit.pushBack(0);
    solution.totalCost = currentlyBest.cost;
    return solution;
}

GeneticSolver::Builder &GeneticSolver::Builder::withPopulation(int population) {
    parameters.population = population;
    return *this;
}

GeneticSolver::Builder &GeneticSolver::Builder::withBreed(int breed) {
    parameters.breed = breed;
    return *this;
}

GeneticSolver::Builder &GeneticSolver::Builder::withCrossoverRate(double rate) {
    parameters.crossoverProbability = rate;
    return *this;
}

GeneticSolver::Builder &GeneticSolver::Builder::withMutationRate(double rate) {
    parameters.mutationProbability = rate;
    return *this;
}

GeneticSolver::Builder &GeneticSolver::Builder::withMutationMethod(MutationMethod method) {
    parameters.mutationMethod = method;
    return *this;
}

GeneticSolver GeneticSolver::Builder::build() {
    auto factory = MutationFactory();
    auto method = factory.createMutation(parameters.mutationMethod);
    GeneticSolver solver(method);
    solver.parameters = parameters;
    return solver;
}
