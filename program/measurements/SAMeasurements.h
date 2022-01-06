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

    SASingleMeasurement measurementForCurrentParameters();

    void save();

    ffstack<std::string> displayedStuff;

    LinkedList<SASingleMeasurement> measurements;
    std::map<std::string, TSPInputMatrix> inputMatrices;
};

std::ostream& operator<<(std::ostream&, SASingleMeasurement&);
std::ostream& operator<<(std::ostream&, SAMeasurements&);

#endif //PEA_SAMEASUREMENTS_H
