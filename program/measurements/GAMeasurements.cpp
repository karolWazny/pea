//
// Created by admin on 05.01.2022.
//

#include <iomanip>
#include <sstream>
#include "GAMeasurements.h"
#include "../../utils/display.h"
#include "../file/AtspFileHandler.h"

const std::string GAMeasurements::headers[6] = {"TIME",
                                          "INSTANCE",
                                          "POPULATION",
                                          "CROSSOVER_RATE",
                                          "MUTATION_RATE",
                                          "MUTATION_METHOD"};

void GAMeasurements::runParametrizedMeasurement() {
    outputFileName = std::string("ga_run-") + timeString() + ".txt";

    measurements = LinkedList<GASingleMeasurement>();
    readInputMatrices();

    measurementsDifferentMutationMethods();
}

void GAMeasurements::measurementsDifferentMutationMethods() {
    clear();
    for(MutationMethod method : mutationMethods){
        currentParameters.mutationMethod = method;

        solver = GeneticSolver::Builder()
                .withMutationMethod(currentParameters.mutationMethod)
                .build();

        displayedStuff.push(std::string("Current mutation method: ") + (std::stringstream() << currentParameters.mutationMethod).str());
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentPopulations();

        displayedStuff.pop();
    }
}

void GAMeasurements::measurementsDifferentPopulations() {
    for(int populationSize : populationSizes){
        currentParameters.population = populationSize;
        displayedStuff.push(std::string("Current population size: ") + std::to_string(currentParameters.population));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentCrossoverRates();

        displayedStuff.pop();
    }
}

void GAMeasurements::measurementsDifferentCrossoverRates() {
    for(double crossoverRate : crossoverRates){
        currentParameters.crossoverProbability = crossoverRate;
        displayedStuff.push(std::string("Current crossover rate: ") + std::to_string(currentParameters.crossoverProbability));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentMutationRates();

        displayedStuff.pop();
    }
}

void GAMeasurements::measurementsDifferentMutationRates() {
    for(double mutationRate : mutationRates){
        currentParameters.mutationProbability = mutationRate;
        displayedStuff.push(std::string("Current mutation rate: ") + std::to_string(currentParameters.mutationProbability));
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

        measurementsDifferentInstances();

        displayedStuff.pop();
    }
}

void GAMeasurements::measurementsDifferentInstances() {
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

GASingleMeasurement GAMeasurements::measurementForCurrentParameters() {
    GASingleMeasurement output;

    solver.setParameters(currentParameters);

    output.instanceFilename = currentFileName;
    output.parameters = currentParameters;
    output.instanceSize = currentInputMatrix.size();

    for(int i = 0; i < 10; i++){
        stopWatch.start();
        auto result = solver.solveFor(currentInputMatrix);
        stopWatch.stop();
        output.time += stopWatch.getLastMeasurementsFloat();
        output.averageCost += result.totalCost;
    }

    output.time /= 10;
    output.averageCost /= 10;

    return output;
}

void GAMeasurements::save() {
    std::ofstream stream(outputFileName);
    stream << *this;
}

void GAMeasurements::readInputMatrices() {
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

std::ostream& operator<<(std::ostream& stream, GAMeasurements& measurements){
    for(int i = 0; i < 5; i++){
        stream << GAMeasurements::headers[i] << '\t';
    }
    stream << GAMeasurements::headers[5] << std::endl;

    auto iterator = measurements.getMeasuredValues().iterator();
    while(iterator.hasNext()){
        stream << iterator.next() << std::endl;
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, GASingleMeasurement& measurement){
    auto& params = measurement.parameters;
    stream << std::to_string(measurement.time) << '\t'
            << measurement.instanceFilename << '\t'
            << std::to_string(params.population) << '\t'
            << std::to_string(params.crossoverProbability) << '\t'
            << std::to_string(params.mutationProbability) << '\t'
            << params.mutationMethod;
    return stream;
};