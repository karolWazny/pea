#ifndef PEA_GENETICSOLVER_H
#define PEA_GENETICSOLVER_H


#include <utility>

#include "../TSPAbstractSolver.h"
#include "Individual.h"
#include "Mutation.h"
#include "../../program/RealRandom.h"

class GeneticSolver : public TSPAbstractSolver {
public:

    class Parameters {
    public:
        int population{30};
        int breed{30};
        double crossoverProbability{1.0};
        double mutationProbability{0.01};
        MutationMethod mutationMethod{MutationMethod::REVERSE};
    };

    class Builder {
    public:
        Builder& withPopulation(int);
        Builder& withBreed(int);
        Builder& withCrossoverRate(double);
        Builder& withMutationRate(double);
        Builder& withMutationMethod(MutationMethod);
        GeneticSolver build();
    private:
        Parameters parameters;
    };

    TSPSolution solveFor(const TSPInputMatrix& input) override;

private:
    explicit GeneticSolver(Mutation mutation) : mutate(std::move(mutation)){};
    void prepareMembers();
    long long calculateCost(const Individual& individual);
    Individual chooseTournamentStyle();
    void applyMutationToBreed();
    void applyCrossoverToBreed();
    void createNewBreed();
    void assessPopulation();
    void setBreedAsParents();

    TSPSolution buildSolutionFromBest();

    static RealRandom<double> random;

    Parameters parameters;
    ffarray<Individual> population;
    ffarray<Individual> breed;
    const TSPInputMatrix* input{};
    Individual currentlyBest;

    Mutation mutate;
    void crossover(Individual&, Individual&);
};

#endif //PEA_GENETICSOLVER_H
