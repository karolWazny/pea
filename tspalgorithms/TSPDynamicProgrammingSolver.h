#ifndef PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
#define PEA_TSPDYNAMICPROGRAMMINGSOLVER_H

#include "TSPAbstractSolver.h"
#include "mathfunctions.h"

class TSPDynamicProgrammingSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;

    static const int BIG_PRIME = 85799449;
private:

    TSPSolution solveRecursively(size_t node);
    TSPSolution recursionEdge(size_t node);
    TSPSolution solveIteratively();
    void prepareMembers(const TSPInputMatrix& inputMatrix);
    void iterationOnLevel(size_t i);
    void iterationForSetWithIndex(size_t i);
    void updateMembersForLevel(size_t i);

    LinkedList<size_t> nodes;
    const TSPInputMatrix* input{};
    Array<Array<TSPSolution>> currentLevel;
    Array<Array<TSPSolution>> previousLevel;
};

#endif //PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
