#ifndef PEA_TSPTABUSEARCHSOLVER_H
#define PEA_TSPTABUSEARCHSOLVER_H

#include "../TSPAbstractSolver.h"
#include "TSPStochasticSolver.h"

class TSPTabuSearchSolver : public TSPStochasticSolver {
public:
    class Parameters{
    public:
        explicit Parameters(int tabuLength = 5, int retries = 1):
                tabuLength(tabuLength), tries(retries){};
        [[nodiscard]]int getTabuLength() const{return tabuLength;};
        [[nodiscard]]int getTries() const{return tries;};
        void setTabuLength(int length){tabuLength = length;};
        void setTries(int retries){ this->tries = retries;};

        static Parameters from(const std::string& string);
        static Parameters from(std::istream& stream);
        std::string parse() const;
    private:
        int tabuLength;
        int tries;
    };
    explicit TSPTabuSearchSolver(int tabuLength = 5, int retries = 1) :
                            params(tabuLength, retries){};
    explicit TSPTabuSearchSolver(Parameters params) : params(params){};
    TSPSolution solveFor(const TSPInputMatrix& matrix) override;

    [[nodiscard]]int getTabuLength() const{return params.getTabuLength();};
    [[nodiscard]]int getTries() const{return params.getTries();};
    void setTabuLength(int length){params.setTabuLength(length);};
    void setTries(int retries){ params.setTries(retries);};
private:
    void prepareForNextTry();
    void prepareMembers(const TSPInputMatrix& matrix);
    void updateMembers();

    void runAlgorithm();

    void evaluateSwapping(size_t index1, size_t index2);
    bool isNotTabu(size_t index1,  size_t index2){
        return iteration - tabu[index1][index2 - index1 - 1] > getTabuLength();
    };
    bool satisfiesAspiration(int potentialCost, size_t index1, size_t index2){
        return potentialCost < bestCost;
    };
    bool isPossiblyBetter(int potentialCost){
        return potentialCost < candidateCost;
    }

    Parameters params;

    ffarray<ffarray<long long>> tabu;

    bool foundNewBest{};
};

#endif //PEA_TSPTABUSEARCHSOLVER_H
