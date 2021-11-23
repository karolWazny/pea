#ifndef PEA_TSPSTOCHASTICSOLVER_H
#define PEA_TSPSTOCHASTICSOLVER_H

#include "../TSPAbstractSolver.h"

class TSPStochasticSolver : public TSPAbstractSolver {
protected:
    const TSPInputMatrix* input{};

    long long bestCost{};
    ffarray<int> bestFound;

    long long currentCost{};
    ffarray<int> state;

    long long candidateCost{};

    long long iteration{};

    size_t firstIndex{};
    size_t secondIndex{};
};


#endif //PEA_TSPSTOCHASTICSOLVER_H
