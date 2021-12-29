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
    Parameters parameters;

};


#endif //PEA_GENETICSOLVER_H
