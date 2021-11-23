#include "TimeMeasurer.h"
#include "../tspalgorithms/deterministic/TSPBruteForceSolver.h"
#include "../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"
#include "../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"
#include <iomanip>

std::string TimeMeasurer::algorithms[3] = {"brute_force", "Held-Karp", "BnB"};
std::string TimeMeasurer::columnHeaders = "TIME\tSIZE\tMETHOD";
TSPAbstractSolver* TimeMeasurer::solvers[3] = {new TSPBruteForceSolver(), new TSPDynamicProgrammingSolver(),
                                              new TSPBranchNBoundSolver()};

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

void TimeMeasurer::runMeasurement() {

    auto startTime = std::time(0);
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

        std::string filename = std::to_string(startTime);
        filename += "meas";
        filename += std::to_string(sizeIndex);
        filename += ".txt";
        std::ofstream ofstream = std::ofstream(filename);

        ofstream << columnHeaders;
        auto iterator = measurements.iterator();
        while(iterator.hasNext()) {
            ofstream << "\n" << iterator.next();
        }

        ofstream.close();

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

        std::string filename = std::to_string(startTime);
        filename += "meas";
        filename += std::to_string(sizeIndex);
        filename += ".txt";
        std::ofstream ofstream = std::ofstream(filename);

        ofstream << columnHeaders;
        auto iterator = measurements.iterator();
        while(iterator.hasNext()) {
            ofstream << "\n" << iterator.next();
        }

        ofstream.close();

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
    std::string filename = std::to_string(startTime);
    filename += "meas.txt";
    std::ofstream ofstream = std::ofstream(filename);

    ofstream << columnHeaders;
    auto iterator = measurements.iterator();
    while(iterator.hasNext()) {
        ofstream << "\n" << iterator.next();
    }
    clear();
}