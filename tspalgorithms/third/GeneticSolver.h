#ifndef PEA_GENETICSOLVER_H
#define PEA_GENETICSOLVER_H


#include "../TSPAbstractSolver.h"

class GeneticSolver : public TSPAbstractSolver {
public:
    enum class MutationMethod{
        REVERSE,
        RANDOM
    };

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

    class Individual{
    public:
        ffarray<int> permutation;
        long long cost{};
    };

    TSPSolution solveFor(const TSPInputMatrix& input) override;

private:
    void prepareMembers();
    long long calculateCost(const Individual& individual);

    Parameters parameters;
    ffarray<Individual> population;
    ffarray<Individual> breed;
    const TSPInputMatrix* input{};
};


#endif //PEA_GENETICSOLVER_H
