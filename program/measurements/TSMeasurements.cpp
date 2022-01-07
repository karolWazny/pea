//
// Created by admin on 06.01.2022.
//

#include <iomanip>
#include "TSMeasurements.h"
#include "../../utils/display.h"
#include "../file/AtspFileHandler.h"

const std::string TSMeasurements::headers[] = {"TIME",
                                               "INSTANCE",
                                               "AVER_COST",
                                               "SIZE",
                                               "TRIES",
                                               "TABU_LENGTH",
                                               "ITERATIONS"};

void TSMeasurements::runParametrizedMeasurement() {
    outputFileName = std::string("ts_run-") + timeString() + ".txt";

    measurements = LinkedList<TSSingleMeasurement>();
    readInputMatrices();

    measurementsDifferentIterations();
}

void TSMeasurements::measurementsDifferentIterations() {
    clear();
    for(auto numberOfIterations : iterations){
        currentParameters.setIterations(numberOfIterations);
        displayedStuff.push(std::string("Current number of iterations: ") + std::to_string(currentParameters.getIterations()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentTries();

        displayedStuff.pop();
    }
    clear();
}

void TSMeasurements::measurementsDifferentTries() {
    for(auto numberOfTries : tries){
        currentParameters.setTries(numberOfTries);
        displayedStuff.push(std::string("Current number of tries: ") + std::to_string(currentParameters.getTries()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentTabuLengths();

        displayedStuff.pop();
    }
}

void TSMeasurements::measurementsDifferentTabuLengths() {
    for(auto tabuLength : tabuLengths){
        currentParameters.setTabuLength(tabuLength);
        displayedStuff.push(std::string("Current tabu length: ") + std::to_string(currentParameters.getTabuLength()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentInstances();

        displayedStuff.pop();
    }
}

void TSMeasurements::measurementsDifferentInstances() {
    for(auto & filename : filenames){
        currentFileName = filename;
        displayedStuff.push(std::string("Current file: ") + currentFileName);
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        currentInputMatrix = inputMatrices[currentFileName];

        measurements.pushBack(measurementForCurrentParameters());

        displayedStuff.pop();
    }
    save();
}

TSSingleMeasurement TSMeasurements::measurementForCurrentParameters() {
    TSSingleMeasurement output;

    solver.setParameters(currentParameters);

    output.instanceFilename = currentFileName;
    output.parameters = currentParameters;
    output.instanceSize = currentInputMatrix.size();

    for(int i = 0; i < 10; i++){
        stopWatch.start();
        auto result = solver.solveFor(inputMatrices[currentFileName]);
        stopWatch.stop();
        output.time += stopWatch.getLastMeasurementsFloat();
        output.averageCost += result.totalCost;
    }

    output.time /= 10;
    output.averageCost /= 10;

    return output;
}

void TSMeasurements::save() {
    std::ofstream stream(outputFileName);
    stream << *this;
}

void TSMeasurements::readInputMatrices() {
    inputMatrices = std::map<std::string, TSPInputMatrix>();

    clear();
    displayedStuff.push(std::string("Reading files..."));
    gotoxy(0, displayedStuff.numberOfElements() - 1);
    std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

    AtspFileHandler fileHandler;
    for(auto & filename : filenames){
        displayedStuff.push(std::string("Current file: ") + filename);
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;
        currentInputMatrix = TSPInputMatrix::from(fileHandler.fromFile(filename));
        inputMatrices.insert({filename, currentInputMatrix});
        displayedStuff.pop();
    }

    displayedStuff.pop();
}

std::ostream& operator<<(std::ostream& stream, TSSingleMeasurement& measurement){
    auto& params = measurement.parameters;
    stream << std::to_string(measurement.time) << '\t'
            << measurement.instanceFilename << '\t'
            << std::to_string(measurement.averageCost) << '\t'
            << std::to_string(measurement.instanceSize) << '\t'
            << std::to_string(params.getTries()) << '\t'
            << std::to_string(params.getTabuLength()) << '\t'
            << std::to_string(params.getIterations()) << '\t';
    return stream;
};
std::ostream& operator<<(std::ostream& stream, TSMeasurements& measurements){
    for(const auto & header : TSMeasurements::headers){
        stream << header << '\t';
    }

    stream << std::endl << std::endl;

    auto iterator = measurements.getMeasuredValues().iterator();
    while(iterator.hasNext()){
        stream << iterator.next() << std::endl;
    }

    return stream;
};

