//
// Created by admin on 06.01.2022.
//

#ifndef PEA_SAMEASUREMENTS_H
#define PEA_SAMEASUREMENTS_H


#include <map>
#include "TimeMeasurer.h"
#include "../../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"

class SASingleMeasurement {
public:
    long double averageCost{};
    long double time{};
    long instanceSize{};
    std::string instanceFilename;
    TSPSimulatedAnnealingSolver::Parameters parameters;
};

class SAMeasurements : public TimeMeasurer{
public:
    void runParametrizedMeasurement();

    static const std::string headers[];

    LinkedList<SASingleMeasurement>& getMeasuredValues(){
        return measurements;
    }
private:
    std::string outputFileName;
    std::string currentFileName;
    TSPInputMatrix currentInputMatrix;

    TSPSimulatedAnnealingSolver solver;
    TSPSimulatedAnnealingSolver::Parameters currentParameters;

    StopWatch stopWatch;

    void readInputMatrices();

    void measurementsDifferentIterations();
    void measurementsDifferentTries();
    void measurementsDifferentMinTemps();
    void measurementsDifferentStartingTemps();
    void measurementsDifferentCoolingFactors();
    void measurementsDifferentInstances();

    SASingleMeasurement measurementForCurrentParameters();

    void save();

    ffstack<std::string> displayedStuff;

    static constexpr double coolingFactors[] = {0.75, 0.8, 0.9, 0.99};
    static constexpr double startingTemps[] = {100.0, 200.0, 500.0, 1000.0, 3000.0};
    static constexpr double minimalTemps[] = {50.0, 10.0, 1.0};
    static constexpr int tries[] = {1, 2, 4, 8};
    static constexpr int iterations[] = {200, 300, 600};

    LinkedList<SASingleMeasurement> measurements;
    std::map<std::string, TSPInputMatrix> inputMatrices;
};

std::ostream& operator<<(std::ostream&, SASingleMeasurement&);
std::ostream& operator<<(std::ostream&, SAMeasurements&);

#endif //PEA_SAMEASUREMENTS_H
