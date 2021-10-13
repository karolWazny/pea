#ifndef PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
#define PEA_TSPDYNAMICPROGRAMMINGSOLVER_H

#include "TSPAbstractSolver.h"
#include "mathfunctions.h"

class TSPDynamicProgrammingSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;

    static const int BIG_PRIME = 85799449;
    class PartialSolution{
    public:
        LinkedList<size_t> circuit;
        RedBlackTree<size_t> nodesUsed;
        size_t lastNode;
        int cost{INT32_MAX};
    };
private:

    TSPSolution solveRecursively(size_t node);
    TSPSolution recursionEdge(size_t node);
    TSPSolution solveIteratively();
    void prepareMembers(const TSPInputMatrix& inputMatrix);
    void iterationOnLevel(size_t i);
    void iterationForSetWithIndex(size_t i);
    void updateMembersForLevel(size_t i);
    size_t size(){
        return input->size();
    }

    LinkedList<size_t> nodes;
    const TSPInputMatrix* input{};
    Array<Array<PartialSolution>> currentLevel;
    Array<Array<PartialSolution>> previousLevel;
};

#endif //PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
