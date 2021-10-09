#ifndef PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
#define PEA_TSPDYNAMICPROGRAMMINGSOLVER_H

#include "TSPAbstractSolver.h"

class TSPDynamicProgrammingSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;
};


#endif //PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
