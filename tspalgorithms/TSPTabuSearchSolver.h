#ifndef PEA_TSPTABUSEARCHSOLVER_H
#define PEA_TSPTABUSEARCHSOLVER_H

#include "TSPAbstractSolver.h"

class TSPTabuSearchSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix& matrix) override;
private:
    const TSPInputMatrix* input{};
};

#endif //PEA_TSPTABUSEARCHSOLVER_H
