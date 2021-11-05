#ifndef SDIZO2_TIMEMEASURER_H
#define SDIZO2_TIMEMEASURER_H

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include "../structure_templates_lib/structures.h"
#include "StopWatch.h"
#include "Randomizer.h"
#include "../tspalgorithms/TSPAbstractSolver.h"

struct SingleMeasurement;

class TimeMeasurer {
public:
    void runMeasurement();
private:

    static constexpr size_t sizes[7] = {4, 6, 8, 10, 12, 15, 20};
    static std::string algorithms[3];
    static std::string columnHeaders;
    static TSPAbstractSolver* solvers[3];
};

struct SingleMeasurement {
public:
    long double time;
    size_t size;
    std::string method;
};


#endif //SDIZO2_TIMEMEASURER_H
