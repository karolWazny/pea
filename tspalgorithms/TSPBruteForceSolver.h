#ifndef PEA_TSPBRUTEFORCESOLVER_H
#define PEA_TSPBRUTEFORCESOLVER_H


#include "TSPAbstractSolver.h"

class TSPBruteForceSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;
};

#endif //PEA_TSPBRUTEFORCESOLVER_H
