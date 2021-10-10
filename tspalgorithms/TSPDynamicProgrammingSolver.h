#ifndef PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
#define PEA_TSPDYNAMICPROGRAMMINGSOLVER_H

#include "TSPAbstractSolver.h"

class TSPDynamicProgrammingSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;
private:
    TSPSolution solveRecursively(size_t node);
    TSPSolution recursionEdge(size_t node);
    void prepareMembers(const TSPInputMatrix& inputMatrix);

    LinkedList<size_t> nodes;
    const TSPInputMatrix* input{};
};

#endif //PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
