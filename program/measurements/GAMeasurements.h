//
// Created by admin on 05.01.2022.
//

#ifndef PEA_GAMEASUREMENTS_H
#define PEA_GAMEASUREMENTS_H


#include <map>
#include "TimeMeasurer.h"
#include "../../tspalgorithms/third/GeneticSolver.h"

struct GASingleMeasurement{
public:
    unsigned long long averageCost{};
    long double time{};
    long instanceSize{};
    std::string instanceFilename;
    GeneticSolver::Parameters parameters;
};

class GAMeasurements : public TimeMeasurer{
public:
    GAMeasurements() : displayedStuff(ffstack<std::string>(10)){};
    void runParametrizedMeasurement();
    LinkedList<GASingleMeasurement>& getMeasuredValues(){
        return measurements;
    }

    static const std::string headers[6];
private:
    std::string outputFileName;
    std::string currentFileName;
    TSPInputMatrix currentInputMatrix;

    GeneticSolver solver;

    GeneticSolver::Parameters currentParameters;

    StopWatch stopWatch;

    void readInputMatrices();

    void measurementsDifferentMutationMethods();
    void measurementsDifferentPopulations();
    void measurementsDifferentCrossoverRates();
    void measurementsDifferentMutationRates();
    void measurementsDifferentInstances();

    GASingleMeasurement measurementForCurrentParameters();

    void save();

    ffstack<std::string> displayedStuff;

    static constexpr int populationSizes[] = {30, 70, 120};
    static constexpr double crossoverRates[] = {0.0, 0.3, 0.6, 0.8, 1.0};
    static constexpr double mutationRates[] = {0.0, 0.01, 0.05, 0.1, 0.3, 0.5, 0.8, 1.0};
    static constexpr MutationMethod mutationMethods[] = {MutationMethod::RANDOM, MutationMethod::REVERSE};

    LinkedList<GASingleMeasurement> measurements;
    std::map<std::string, TSPInputMatrix> inputMatrices;
};

std::ostream& operator<<(std::ostream&, GASingleMeasurement&);
std::ostream& operator<<(std::ostream&, GAMeasurements&);


#endif //PEA_GAMEASUREMENTS_H
