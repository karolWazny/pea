#ifndef PEA_GENETICSOLVER_H
#define PEA_GENETICSOLVER_H


#include "../TSPAbstractSolver.h"
#include "Individual.h"
#include "Mutation.h"
#include "../../program/RealRandom.h"

class GeneticSolver : public TSPAbstractSolver {
public:

    class Parameters {
    public:
        int population{};
        int breed{};
        double crossoverProbability{};
        double mutationProbability{};
        MutationMethod mutationMethod{MutationMethod::REVERSE};
    };

    class Builder {
    public:

    private:
        Parameters parameters;
    };

    TSPSolution solveFor(const TSPInputMatrix& input) override;

private:
    void prepareMembers();
    long long calculateCost(const Individual& individual);
    Individual chooseTournamentStyle();
    void applyMutationToBreed();
    void applyCrossoverToBreed();
    void createNewBreed();
    void assessPopulation();
    void setBreedAsParents();

    static RealRandom<double> random;

    Parameters parameters;
    ffarray<Individual> population;
    ffarray<Individual> breed;
    const TSPInputMatrix* input{};
    Individual currentlyBest;

    std::function<void(Individual&)> mutate;
    void crossover(Individual&, Individual&);
};

#endif //PEA_GENETICSOLVER_H
