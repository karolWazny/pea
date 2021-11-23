#ifndef PEA_TSPTABUSEARCHSOLVER_H
#define PEA_TSPTABUSEARCHSOLVER_H

#include "TSPAbstractSolver.h"

class TSPTabuSearchSolver : public TSPAbstractSolver {
public:
    TSPSolution solveFor(const TSPInputMatrix& matrix) override;
private:
    const TSPInputMatrix* input{};

    void calculateCurrentCost();
    void prepareMembers(const TSPInputMatrix& matrix);
    TSPSolution buildSolution();
    void updateMembers();

    void runAlgorithm();
    [[nodiscard]] int candidateSolution(size_t index1, size_t index2) const;

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

    size_t firstIndex{};
    size_t secondIndex{};

    size_t iteration{};

    int candidateCost{};

    int tabuLength{5};

    int bestCost{};
    ffarray<int> bestState;

    int currentCost{};
    ffarray<int> state;

    ffarray<ffarray<int>> tabu;

    bool foundNewBest{};
};

#endif //PEA_TSPTABUSEARCHSOLVER_H
