#ifndef PEA_TSPBRANCHNBOUNDSOLVER_H
#define PEA_TSPBRANCHNBOUNDSOLVER_H

#include "TSPAbstractSolver.h"

class TSPBranchNBoundSolver : public TSPAbstractSolver{
public:
    TSPSolution solveFor(const TSPInputMatrix& inputMatrix) override;
};


#endif //PEA_TSPBRANCHNBOUNDSOLVER_H
