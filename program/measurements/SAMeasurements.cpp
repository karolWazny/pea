//
// Created by admin on 06.01.2022.
//

#include <iomanip>
#include "SAMeasurements.h"
#include "../file/AtspFileHandler.h"
#include "../../utils/display.h"

const std::string SAMeasurements::headers[] = {"TIME",
                                                "INSTANCE",
                                                "AVER_COST",
                                                "SIZE",
                                                "TRIES",
                                                "START_TEMP",
                                                "MIN_TEMP",
                                                "COOLING",
                                                "ITERATIONS"};

void SAMeasurements::runParametrizedMeasurement() {
    outputFileName = std::string("sa_run-") + timeString() + ".txt";

    measurements = LinkedList<SASingleMeasurement>();
    readInputMatrices();

    measurementsDifferentIterations();
}

void SAMeasurements::measurementsDifferentIterations() {
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

void SAMeasurements::measurementsDifferentTries() {
    for(auto numberOfTries : tries){
        currentParameters.setTries(numberOfTries);
        displayedStuff.push(std::string("Current number of tries: ") + std::to_string(currentParameters.getTries()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentMinTemps();

        displayedStuff.pop();
    }
}

void SAMeasurements::measurementsDifferentMinTemps() {
    for(double minTemp : minimalTemps){
        currentParameters.setMinimalTemp(minTemp);
        displayedStuff.push(std::string("Current minimal temperature: ") + std::to_string(currentParameters.getMinimalTemp()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentStartingTemps();

        displayedStuff.pop();
    }
}

void SAMeasurements::measurementsDifferentStartingTemps() {
    for(double startingTemp : startingTemps){
        currentParameters.setStartTemp(startingTemp);
        displayedStuff.push(std::string("Current starting temperature: ") + std::to_string(currentParameters.getStartTemp()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentCoolingFactors();

        displayedStuff.pop();
    }
}

void SAMeasurements::measurementsDifferentCoolingFactors() {
    for(double coolingFactor : coolingFactors){
        currentParameters.setCoolingConstant(coolingFactor);
        displayedStuff.push(std::string("Current cooling factor: ") + std::to_string(currentParameters.getCoolingConstant()));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentInstances();

        displayedStuff.pop();
    }
}

void SAMeasurements::measurementsDifferentInstances() {
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

SASingleMeasurement SAMeasurements::measurementForCurrentParameters() {
    SASingleMeasurement output;

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

void SAMeasurements::readInputMatrices() {
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

void SAMeasurements::save() {
    std::ofstream stream(outputFileName);
    stream << *this;
}

std::ostream& operator<<(std::ostream& stream, SASingleMeasurement& measurement){
    auto& params = measurement.parameters;
    stream << std::to_string(measurement.time) << '\t'
            << measurement.instanceFilename << '\t'
            << std::to_string(measurement.averageCost) << '\t'
            << std::to_string(measurement.instanceSize) << '\t'
            << std::to_string(params.getTries()) << '\t'
            << std::to_string(params.getStartTemp()) << '\t'
            << std::to_string(params.getMinimalTemp()) << '\t'
            << std::to_string(params.getCoolingConstant()) << '\t'
            << std::to_string(params.getIterations()) << '\t';
    return stream;
};
std::ostream& operator<<(std::ostream& stream, SAMeasurements& measurements){
    for(const auto & header : SAMeasurements::headers){
        stream << header << '\t';
    }

    stream << std::endl << std::endl;

    auto iterator = measurements.getMeasuredValues().iterator();
    while(iterator.hasNext()){
        stream << iterator.next() << std::endl;
    }

    return stream;
}