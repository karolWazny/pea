#ifndef PEA_TSPBRUTEFORCESOLVER_H
#define PEA_TSPBRUTEFORCESOLVER_H


#include "../TSPAbstractSolver.h"

class TSPBruteForceSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;
private:
    bool nextPermutation();
    void compareCurrentPermutation();

    size_t* allNodes{};
    const TSPInputMatrix* inputMatrix{};
    TSPSolution solution;
};

#endif //PEA_TSPBRUTEFORCESOLVER_H
