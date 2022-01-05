//
// Created by admin on 05.01.2022.
//

#ifndef PEA_GAMEASUREMENTS_H
#define PEA_GAMEASUREMENTS_H


#include "TimeMeasurer.h"
#include "../../tspalgorithms/third/GeneticSolver.h"

struct GASingleMeasurement{
public:
    long double time;
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
    ffstack<std::string> displayedStuff;

    LinkedList<GASingleMeasurement> measurements;

};

std::ostream& operator<<(std::ostream&, GASingleMeasurement&);
std::ostream& operator<<(std::ostream&, GAMeasurements&);


#endif //PEA_GAMEASUREMENTS_H
