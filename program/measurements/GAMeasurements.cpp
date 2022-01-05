//
// Created by admin on 05.01.2022.
//

#include <iomanip>
#include "GAMeasurements.h"
#include "../../utils/display.h"

void GAMeasurements::runParametrizedMeasurement() {
    auto filename = timeString() + ".txt";
    for(int i = 0; i < filesAmount; i++){
        clear();
        displayedStuff.push(std::string("Current file: ") + filenames[i]);
        gotoxy(0, displayedStuff.numberOfElements() - 1);
        std::cout << std::left << std::setw(50) << displayedStuff.getCurrent() << std::endl;

    }
}
