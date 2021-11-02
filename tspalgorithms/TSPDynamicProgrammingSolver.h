#ifndef PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
#define PEA_TSPDYNAMICPROGRAMMINGSOLVER_H

#include "TSPAbstractSolver.h"
#include "mathfunctions.h"
#include "../structure_templates_lib/array_lib/ffarray.h"

class TSPDynamicProgrammingSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;

    class PartialSolution{
    public:
        LinkedList<size_t> circuit;
        RedBlackTree<size_t> nodesUsed;
        size_t lastNode{};
        int cost{INT32_MAX};
    };
private:

    TSPSolution solveIteratively();
    void prepareMembers(const TSPInputMatrix& inputMatrix);
    void iterationOnLevel();
    void iterationForCurrentSet();
    void updateMembersForCurrentLevel();
    size_t size(){
        return input->size();
    }

    LinkedList<size_t> nodes;
    const TSPInputMatrix* input{};
    ffarray<ffarray<PartialSolution>> currentLevel;
    ffarray<ffarray<PartialSolution>> previousLevel;

    size_t currentLevelIndex{};
    size_t currentSetIndex{};
};

#endif //PEA_TSPDYNAMICPROGRAMMINGSOLVER_H
