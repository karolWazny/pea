#ifndef PEA_TSPBRUTEFORCESOLVER_H
#define PEA_TSPBRUTEFORCESOLVER_H


#include "TSPAbstractSolver.h"

class TSPBruteForceSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix &) override;
private:
    void goDeeper();
    void compareAndUpdateBestPath();

    LinkedList<size_t> currentBranch;
    LinkedList<size_t> unusedNodes;
    const TSPInputMatrix* inputMatrix{};
    TSPSolution solution;
};

#endif //PEA_TSPBRUTEFORCESOLVER_H
