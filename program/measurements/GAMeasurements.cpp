//
// Created by admin on 05.01.2022.
//

#include <iomanip>
#include "GAMeasurements.h"
#include "../../utils/display.h"

const std::string GAMeasurements::headers[6] = {"TIME",
                                          "INSTANCE",
                                          "POPULATION",
                                          "CROSSOVER_RATE",
                                          "MUTATION_RATE",
                                          "MUTATION_METHOD"};

void GAMeasurements::runParametrizedMeasurement() {
    auto filename = timeString() + ".txt";
    for(int i = 0; i < filesAmount; i++){
        clear();
        displayedStuff.push(std::string("Current file: ") + filenames[i]);
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

    }
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