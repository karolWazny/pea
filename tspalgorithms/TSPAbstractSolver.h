#ifndef PEA_TSPABSTRACTSOLVER_H
#define PEA_TSPABSTRACTSOLVER_H

#include "TSPInputMatrix.h"
#include "TSPSolution.h"

class TSPAbstractSolver {
public:
    virtual TSPSolution solveFor(const TSPInputMatrix&) = 0;
};

#endif //PEA_TSPABSTRACTSOLVER_H
