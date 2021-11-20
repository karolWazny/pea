#ifndef PEA_TSPSIMULATEDANNEALINGSOLVER_H
#define PEA_TSPSIMULATEDANNEALINGSOLVER_H

#include "TSPAbstractSolver.h"
#include "../program/RealRandom.h"
#include "../program/Randomizer.h"

class TSPSimulatedAnnealingSolver : public TSPAbstractSolver {
public:
    explicit TSPSimulatedAnnealingSolver(double temperature = 5000,
                                double coolingConstant = 0.999,
                                size_t iterations = 20,
                                double minimalTemperature = 50,
                                int tries = 1)
                                : startTemp(temperature),
                                coolingConstant(coolingConstant < 1.0 ? coolingConstant : 0.99),
                                iterations(iterations),
                                minimalTemperature(minimalTemperature),
                                tries(tries){};

    TSPSolution solveFor(const TSPInputMatrix& matrix) override;

    void setStartTemp(double startTemp);
    void setCoolingConstant(double coolingConstant);
    void setIterations(size_t iterations);
    void setMinimalTemperature(double minimalTemperature);
    [[nodiscard]] double getStartTemp() const;
    [[nodiscard]] double getCoolingConstant() const;
    [[nodiscard]] size_t getIterations() const;
    [[nodiscard]] double getMinimalTemperature() const;

private:
    static RealRandom<double> realRandom;
    static Randomizer intRandom;

    void prepareMembers(const TSPInputMatrix& matrix);
    void calculateCandidateCost();
    TSPSolution buildSolution();
    void calculateIndexesForNextMove();
    void calculateNextCandidateSolution();
    void swapVertices();
    void rollbackSwapVertices(){
        swapVertices();
    };
    void recalculateCandidateCost();
    void updateBest(){
        bestCost = candidateCost;
        bestFound = state.copy();
    };
    void updateParameters(){
        currentTemp *= coolingConstant;
    };
    void evaluateCandidateSolution();
    [[nodiscard]] bool acceptStochastically() const;
    [[nodiscard]] bool acceptDeterministically() const{
        return candidateCost <= currentCost;
    };
    [[nodiscard]] double probability() const{
        return exp(double(currentCost - candidateCost)/currentTemp);
    };
    bool acceptCandidate(){
        if(acceptDeterministically())
            return true;
        else
            return acceptStochastically();
    };
    void prepareForNextTry();

    int tries;

    const TSPInputMatrix* input{};
    double startTemp;
    double minimalTemperature;
    double currentTemp{};
    double coolingConstant;
    size_t iterations;
    size_t currentIteration{};

    ffarray<int> state;
    long long currentCost{};
    long long candidateCost{};

    ffarray<int> bestFound;
    long long bestCost{};

    size_t index{};
    size_t secondIndex{};
    size_t preIndex{};
    size_t postIndex{};

    [[nodiscard]] bool keepGoing() const{
        return currentTemp > minimalTemperature && currentIteration < iterations;
    };
};

#endif //PEA_TSPSIMULATEDANNEALINGSOLVER_H
