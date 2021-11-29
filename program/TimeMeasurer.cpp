#include "TimeMeasurer.h"
#include "../tspalgorithms/deterministic/TSPBruteForceSolver.h"
#include "../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"
#include "../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"
#include "../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"
#include "../tspalgorithms/stochastic/TSPTabuSearchSolver.h"
#include <iomanip>
#include <chrono>
#include <sstream>

std::string TimeMeasurer::algorithms[5] = {"brute_force", "Held-Karp", "BnB", "SA", "TS"};
std::string TimeMeasurer::columnHeaders = "TIME\tSIZE\tMETHOD";
std::unique_ptr<TSPAbstractSolver> TimeMeasurer::solvers[5] = {std::unique_ptr<TSPAbstractSolver>(new TSPBruteForceSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPDynamicProgrammingSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPBranchNBoundSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPSimulatedAnnealingSolver()),
                std::unique_ptr<TSPAbstractSolver>(new TSPTabuSearchSolver())};

void gotoxy(short x, short y)
{
    COORD coord;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}

void clear() {
    system("cls");
}

std::ostream& operator<<(std::ostream& ostream, const SingleMeasurement meas) {
    ostream << std::to_string(meas.time) << "\t"
            << std::to_string(meas.size) << "\t"
            << meas.method;
    return ostream;
}

std::string timeString(){
    std::stringstream output;
    const auto timePoint = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(timePoint);
    output << std::put_time(std::localtime(&t_c), "%F_%T");
    auto outputString = output.str();
    std::replace(outputString.begin(), outputString.end(), ':', '-');
    return outputString;
}

void TimeMeasurer::writeToFile(std::string filename, LinkedList<SingleMeasurement> elements){
    std::ofstream ofstream = std::ofstream(filename);

    ofstream << columnHeaders;
    auto iterator = elements.iterator();
    while(iterator.hasNext()) {
        ofstream << "\n" << iterator.next();
    }
}

void TimeMeasurer::runMeasurement() {

    std::string filename = timeString() + ".txt";
    LinkedList<SingleMeasurement> measurements;
    auto stopWatch = StopWatch();
    clear();
    gotoxy(0,0);
    std::cout << "PERFORMING MEASUREMENTS\n";
    std::cout << "Size:\nInstance:\nAlgorithm:";
    for(int sizeIndex = 0; sizeIndex < 5; sizeIndex++){

        gotoxy(7, 1);
        std::cout << std::right << std::setw(2) << std::to_string(sizes[sizeIndex]);
        std::cout << " (" << std::to_string(sizeIndex + 1) << " out of " << std::to_string(7)
                << ")";

        writeToFile(filename, measurements);

        long double times[3] = {0, 0, 0};
        for(int i = 0; i < 100; i++){
            gotoxy(10, 2);
            std::cout << std::right << std::setw(3) << std::to_string(i + 1)
                        << " out of 100";
            auto problemInstance = randomMatrix(sizes[sizeIndex]);
            for(int solverIndex = 0; solverIndex < 3; solverIndex ++) {
                gotoxy(11, 3);
                std::cout << std::setw(20) << algorithms[solverIndex]
                        << " (" << std::to_string(solverIndex + 1) << " out of "
                        << std::to_string(3) << ")";
                stopWatch.start();
                auto result = solvers[solverIndex]->solveFor(problemInstance);
                stopWatch.stop();
                if(result.totalCost == 10){
                    result.totalCost++;
                }
                times[solverIndex] += stopWatch.getLastMeasurementsFloat();
            }
        }
        for(int solverIndex = 0; solverIndex < 3; solverIndex++){
            SingleMeasurement measurement;
            measurement.method = algorithms[solverIndex];
            measurement.size = sizes[sizeIndex];
            measurement.time = times[solverIndex];
            measurements.pushBack(measurement);
        }
    }

    for(int sizeIndex = 5; sizeIndex < 7; sizeIndex++){

        gotoxy(7, 1);
        std::cout << std::right << std::setw(2) << std::to_string(sizes[sizeIndex]);
        std::cout << " (" << std::to_string(sizeIndex + 1) << " out of " << std::to_string(7)
                  << ")";

        writeToFile(filename, measurements);

        unsigned long long times[3] = {0, 0, 0};
        for(int i = 0; i < 100; i++){
            gotoxy(10, 2);
            std::cout << std::right << std::setw(3) << std::to_string(i + 1)
                      << " out of 100";
            auto problemInstance = randomMatrix(sizes[sizeIndex]);
            for(int solverIndex = 1; solverIndex < 3; solverIndex ++) {
                gotoxy(11, 3);
                std::cout << std::setw(20) << algorithms[solverIndex]
                          << " (" << std::to_string(solverIndex + 1) << " out of "
                          << std::to_string(3) << ")";
                stopWatch.start();
                auto result = solvers[solverIndex]->solveFor(problemInstance);
                stopWatch.stop();
                if(result.totalCost == 10){
                    result.totalCost++;
                }
                times[solverIndex] += stopWatch.getLastMeasurmentPiccosec();
            }
        }
        for(int solverIndex = 1; solverIndex < 3; solverIndex++){
            SingleMeasurement measurement;
            measurement.method = algorithms[solverIndex];
            measurement.size = sizes[sizeIndex];
            measurement.time = times[solverIndex];
            measurements.pushBack(measurement);
        }
    }

    std::cout << "\n";
    writeToFile(filename, measurements);
    clear();
}