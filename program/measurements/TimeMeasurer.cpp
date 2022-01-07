#include "TimeMeasurer.h"
#include "../../tspalgorithms/deterministic/TSPBruteForceSolver.h"
#include "../../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"
#include "../../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"
#include "../../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"
#include "../../tspalgorithms/stochastic/TSPTabuSearchSolver.h"
#include "../../utils/display.h"
#include "../file/AtspFileHandler.h"
#include "../../utils/stringutils.h"
#include <iomanip>
#include <chrono>
#include <sstream>

#include <filesystem>

std::vector<std::string> TimeMeasurer::filenames = TimeMeasurer::loadFilenamesFromWorkingDirectory();

const std::string TimeMeasurer::algorithms[] = {"brute_force", "BnB", "Held-Karp"};
std::string TimeMeasurer::columnHeaders = "SIZE\tTIME\tMETHOD";
std::unique_ptr<TSPAbstractSolver> TimeMeasurer::solvers[] = {std::unique_ptr<TSPAbstractSolver>(new TSPBruteForceSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPBranchNBoundSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPDynamicProgrammingSolver())};

std::ostream& operator<<(std::ostream& ostream, const SingleMeasurement meas) {
    ostream << std::to_string(meas.size) << "\t"
            << std::to_string(meas.time) << "\t"
            << meas.method;
    return ostream;
}

std::string TimeMeasurer::timeString(){
    std::stringstream output;
    const auto timePoint = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(timePoint);
    output << std::put_time(std::localtime(&t_c), "%F_%T");
    auto outputString = output.str();
    std::replace(outputString.begin(), outputString.end(), ':', '-');
    return outputString;
}

void TimeMeasurer::writeToFile(){
    std::ofstream ofstream = std::ofstream(filename);

    ofstream << columnHeaders;
    auto iterator = measurements.iterator();
    while(iterator.hasNext()) {
        ofstream << "\n" << iterator.next();
    }
}

void TimeMeasurer::runMeasurement() {
    filename = timeString() + "-all_solvers.txt";
    measurements = LinkedList<SingleMeasurement>();
    prepareDisplay();
    sizeIndex = 0;

    someMeasurements(5, 0);

    someMeasurements(7, 1);

    std::cout << "\n";
    writeToFile();
    clear();
}

void TimeMeasurer::someMeasurements(int upperSizeIndexBound, int lowerSolverIndexBound) {
    for(; sizeIndex < upperSizeIndexBound; sizeIndex++){

        gotoxy(7, 1);
        std::cout << std::right << std::setw(2) << std::to_string(sizes[sizeIndex]);
        std::cout << " (" << std::to_string(sizeIndex + 1) << " out of " << std::to_string(sizesAmount)
                  << ")";

        writeToFile();

        long double times[3] = {0, 0, 0};
        for(int i = 0; i < 100; i++){
            gotoxy(10, 2);
            std::cout << std::right << std::setw(3) << std::to_string(i + 1)
                      << " out of 100";
            auto problemInstance = randomMatrix(sizes[sizeIndex]);
            for(int solverIndex = lowerSolverIndexBound; solverIndex < 5; solverIndex ++) {
                gotoxy(11, 3);
                std::cout << std::setw(20) << algorithms[solverIndex]
                          << " (" << std::to_string(solverIndex + 1) << " out of "
                          << std::to_string(algorithmsAmount) << ")";
                stopWatch.start();
                auto result = solvers[solverIndex]->solveFor(problemInstance);
                stopWatch.stop();
                if(result.totalCost == 10){
                    result.totalCost++;
                }
                times[solverIndex] += stopWatch.getLastMeasurementsFloat();
            }
        }
        for(int solverIndex = lowerSolverIndexBound; solverIndex < 3; solverIndex++){
            SingleMeasurement measurement;
            measurement.method = algorithms[solverIndex];
            measurement.size = sizes[sizeIndex];
            measurement.time = times[solverIndex] / 100;
            measurements.pushBack(measurement);
        }
    }
}

void TimeMeasurer::prepareDisplay() {
    clear();
    gotoxy(0,0);
    std::cout << "PERFORMING MEASUREMENTS\n";
    std::cout << "Size:\nInstance:\nAlgorithm:";
}

void TimeMeasurer::runMeasurement(const std::string & instanceFilename) {
    auto outputFile = timeString() + "-dp_bnb-" + instanceFilename + ".txt";
    std::ofstream stream(outputFile);
    stream << columnHeaders << std::endl;
    stream.close();
    AtspFileHandler fileHandler;
    TSPInputMatrix instance = TSPInputMatrix::from(fileHandler.fromFile(instanceFilename));
    LinkedList<SingleMeasurement> singleMeasurements;
    for(int i = 1; i < 3; i++){
        SingleMeasurement measurement;
        measurement.method = algorithms[i];
        measurement.size = instance.size();
        for(int j = 0; j < 10; j++){
            stopWatch.start();
            auto result = solvers[i]->solveFor(instance);
            stopWatch.stop();
            result.totalCost++;
            measurement.time += stopWatch.getLastMeasurementsFloat();
        }
        measurement.time /= 10;
        singleMeasurements.pushBack(measurement);
    }
    stream.open(outputFile);
    stream << columnHeaders << std::endl;
    auto iterator = singleMeasurements.iterator();
    while(iterator.hasNext()){
        stream << iterator.next() << std::endl;
    }
}

std::vector<std::string> TimeMeasurer::loadFilenamesFromWorkingDirectory() {
    std::vector<std::string> output;

    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path = cwd.string();
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        if(hasEnding(entry.path().filename().string(), ".atsp"))
            output.push_back(entry.path().filename().string());
    }

    return output;
}
