//
// Created by admin on 05.01.2022.
//

#ifndef PEA_GAMEASUREMENTS_H
#define PEA_GAMEASUREMENTS_H


#include "TimeMeasurer.h"

class GAMeasurements : public TimeMeasurer{
public:
    GAMeasurements() : displayedStuff(ffstack<std::string>(10)){};
    void runParametrizedMeasurement();
private:
    ffstack<std::string> displayedStuff;
};

struct GASingleMeasurement{
public:
    long double time;
    std::string instanceFilename;

};


#endif //PEA_GAMEASUREMENTS_H
