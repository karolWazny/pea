#ifndef PEA_TSPSIMULATEDANNEALINGSOLVER_H
#define PEA_TSPSIMULATEDANNEALINGSOLVER_H

#include "TSPAbstractSolver.h"

class TSPSimulatedAnnealingSolver : public TSPAbstractSolver {
public:
    explicit TSPSimulatedAnnealingSolver(double temperature = 500,
                                double coolingConstant = 0.99,
                                size_t iterations = 10000,
                                double minimalTemperature = 50):startTemp(temperature),
                                coolingConstant(coolingConstant),
                                iterations(iterations),
                                minimalTemperature(minimalTemperature){};

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
    void prepareMembers(const TSPInputMatrix& matrix);

    const TSPInputMatrix* input{};
    double startTemp;
    double minimalTemperature;
    double currentTemp{};
    double coolingConstant;
    size_t iterations;
    size_t currentIteration{};

    ffarray<int> state;
    size_t currentCost{};

    ffarray<int> bestFound;
    size_t bestCost{};

    [[nodiscard]] bool keepGoing() const{
        return currentTemp > minimalTemperature && currentIteration < iterations;
    };
};

#endif //PEA_TSPSIMULATEDANNEALINGSOLVER_H
