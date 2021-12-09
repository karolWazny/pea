#ifndef SDIZO2_TIMEMEASURER_H
#define SDIZO2_TIMEMEASURER_H

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include "../../structure_templates_lib/structures.h"
#include "../StopWatch.h"
#include "../Randomizer.h"
#include "../../tspalgorithms/TSPAbstractSolver.h"

struct SingleMeasurement;

class TimeMeasurer {
public:
    void runMeasurement();
private:

    void writeToFile();
    void someMeasurements(int upperSizeIndexBound, int lowerSolverIndexBound);

    void prepareDisplay();

    static constexpr int sizesAmount = 10;
    static constexpr int algorithmsAmount = 5;

    static constexpr size_t sizes[sizesAmount] = {4, 6, 8, 10, 12, 15, 20, 30, 50, 100};
    static std::string algorithms[algorithmsAmount];
    static std::string columnHeaders;
    static std::unique_ptr<TSPAbstractSolver> solvers[algorithmsAmount];
    int sizeIndex{};

    LinkedList<SingleMeasurement> measurements;
    StopWatch stopWatch;
    std::string filename;
};

struct SingleMeasurement {
public:
    long double time;
    size_t size;
    std::string method;
};


#endif //SDIZO2_TIMEMEASURER_H
