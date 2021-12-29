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
        MutationMethod mutationMethod{};
    };

    class Builder {
    private:
        MutationMethod mutationMethod{MutationMethod::REVERSE};
        int population{30};
        int breed{90};
        double crossoverProbability{0.6};
        double mutationProbability{0.01};
    };

private:

};


#endif //PEA_GENETICSOLVER_H
