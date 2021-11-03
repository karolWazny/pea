#ifndef PEA_TSPBRANCHNBOUNDSOLVER_H
#define PEA_TSPBRANCHNBOUNDSOLVER_H

#include "TSPAbstractSolver.h"
#include "../structure_templates_lib/structures.h"

class TSPBranchNBoundSolver : public TSPAbstractSolver{
public:
    TSPSolution solveFor(const TSPInputMatrix& inputMatrix) override;
private:
    void prepareMembers(const TSPInputMatrix& inputMatrix);
    void solveRecursively(int heuristicSoFar);
    int calculateHeuristic(int previousHeuristic, size_t nextNode);
    void updateSolution(int cost);

    ffqueue<size_t> unusedNodes;
    ffstack<size_t> currentPath;
    int minimalValue{};
    Array<int> minOuts{};
    const TSPInputMatrix* input{};
    TSPSolution solution{};
};

#endif //PEA_TSPBRANCHNBOUNDSOLVER_H
