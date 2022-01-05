#ifndef PEA_TSPSIMULATEDANNEALINGSOLVER_H
#define PEA_TSPSIMULATEDANNEALINGSOLVER_H

#include "../../utils/RealRandom.h"
#include "../../utils/Randomizer.h"
#include "TSPStochasticSolver.h"

class TSPSimulatedAnnealingSolver : public TSPStochasticSolver {
public:
    explicit TSPSimulatedAnnealingSolver(double temperature = 5000,
                                double coolingConstant = 0.999,
                                size_t iterations = 20,
                                double minimalTemperature = 50,
                                int tries = 1)
                                : params(temperature,
                                         coolingConstant,
                                         iterations,
                                         minimalTemperature,
                                         tries){};

    class Parameters{
    public:
        explicit Parameters(double temperature = 5000,
                            double coolingConstant = 0.999,
                            size_t iterations = 20,
                            double minimalTemperature = 50,
                            int tries = 1)
                : startTemp(temperature),
                  coolingConstant(coolingConstant < 1.0 ? coolingConstant : 0.99),
                  iterations(iterations),
                  minimalTemp(minimalTemperature),
                  tries(tries){};
        static Parameters from(const std::string& string);
        static Parameters from(std::istream& stream);
        std::string parse() const;
        [[nodiscard]] int getTries() const{return tries;}
        [[nodiscard]] double getStartTemp() const{return startTemp;}
        [[nodiscard]] double getMinimalTemp() const{return minimalTemp;}
        [[nodiscard]] double getCoolingConstant() const{return coolingConstant;}
        [[nodiscard]] size_t getIterations() const{return iterations;}
        void setTries(int tries){this->tries = tries;}
        void setStartTemp(double startTemp){this->startTemp = startTemp;}
        void setMinimalTemp(double minimalTemp){this->minimalTemp = minimalTemp;}
        void setCoolingConstant(double coolingConstant){this->coolingConstant = (coolingConstant < 1.0 ? coolingConstant : 0.99);}
        void setIterations(size_t iterations){this->iterations = iterations;}
    private:
        int tries;
        double startTemp;
        double minimalTemp;
        double coolingConstant;
        size_t iterations;
    };

    explicit TSPSimulatedAnnealingSolver(Parameters params) : params(params){};

    TSPSolution solveFor(const TSPInputMatrix& matrix) override;

    void setStartTemp(double startTemp);
    void setCoolingConstant(double coolingConstant);
    void setIterations(size_t iterations);
    void setMinimalTemperature(double minimalTemperature);
    void setTries(int tries);
    void setParameters(Parameters parameters);
    [[nodiscard]] double getStartTemp() const;
    [[nodiscard]] double getCoolingConstant() const;
    [[nodiscard]] size_t getIterations() const;
    [[nodiscard]] double getMinimalTemperature() const;
    [[nodiscard]] int getTries() const;



private:
    static RealRandom<double> realRandom;
    static Randomizer intRandom;

    void prepareMembers(const TSPInputMatrix& matrix);
    void calculateIndexesForNextMove();
    void calculateNextCandidateSolution();
    void swapVertices();
    void rollbackSwapVertices(){
        swapVertices();
    };
    void updateBest(){
        bestCost = candidateCost;
        bestFound = state.copy();
    };
    void updateParameters(){
        currentTemp *= getCoolingConstant();
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

    Parameters params;

    double currentTemp{};

    [[nodiscard]] bool keepGoing() const{
        return currentTemp > getMinimalTemperature();
    };
};

#endif //PEA_TSPSIMULATEDANNEALINGSOLVER_H
