//
// Created by admin on 06.01.2022.
//

#ifndef PEA_TSMEASUREMENTS_H
#define PEA_TSMEASUREMENTS_H


#include <map>
#include "TimeMeasurer.h"
#include "../../tspalgorithms/stochastic/TSPTabuSearchSolver.h"

class TSSingleMeasurement{
public:
    long double averageCost{};
    long double time{};
    long instanceSize{};
    std::string instanceFilename;
    TSPTabuSearchSolver::Parameters parameters;
};

class TSMeasurements : public TimeMeasurer{
public:
    TSMeasurements() : displayedStuff(ffstack<std::string>(10)){};
    LinkedList<TSSingleMeasurement>& getMeasuredValues(){
        return measurements;
    }
    void runParametrizedMeasurement();

    static const std::string headers[];
private:
    std::string outputFileName;
    std::string currentFileName;
    TSPInputMatrix currentInputMatrix;

    TSPTabuSearchSolver solver;
    TSPTabuSearchSolver::Parameters currentParameters;

    StopWatch stopWatch;

    ffstack<std::string> displayedStuff;
    LinkedList<TSSingleMeasurement> measurements;
    std::map<std::string, TSPInputMatrix> inputMatrices;

    TSSingleMeasurement measurementForCurrentParameters();

    void save();
    void readInputMatrices();

    void measurementsDifferentIterations();
    void measurementsDifferentTries();
    void measurementsDifferentTabuLengths();
    void measurementsDifferentInstances();

    static constexpr int tabuLengths[] = {30, 70, 150, 300};
    static constexpr int tries[] = {1, 2, 4, 8};
    static constexpr int iterations[] = {500, 800, 1500};
};

std::ostream& operator<<(std::ostream&, TSSingleMeasurement&);
std::ostream& operator<<(std::ostream&, TSMeasurements&);

#endif //PEA_TSMEASUREMENTS_H
