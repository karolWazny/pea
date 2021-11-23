#ifndef PEA_TSPTABUSEARCHSOLVER_H
#define PEA_TSPTABUSEARCHSOLVER_H

#include "../TSPAbstractSolver.h"
#include "TSPStochasticSolver.h"

class TSPTabuSearchSolver : public TSPStochasticSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix& matrix) override;
private:
    void calculateCurrentCost();
    void prepareMembers(const TSPInputMatrix& matrix);
    TSPSolution buildSolution();
    void updateMembers();

    void runAlgorithm();
    [[nodiscard]] long long candidateSolution(size_t index1, size_t index2) const;

    void evaluateSwapping(size_t index1, size_t index2);
    bool isNotTabu(size_t index1,  size_t index2){
        return iteration - tabu[index1][index2 - index1 - 1] > tabuLength;
    };
    bool satisfiesAspiration(int potentialCost, size_t index1, size_t index2){
        return potentialCost < bestCost;
    };
    bool isPossiblyBetter(int potentialCost){
        return potentialCost < candidateCost;
    }

    int tabuLength{5};

    ffarray<ffarray<long long>> tabu;

    bool foundNewBest{};
};

#endif //PEA_TSPTABUSEARCHSOLVER_H
