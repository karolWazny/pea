#ifndef SDIZO2_MAIN_H
#define SDIZO2_MAIN_H

#include <string>
#include <iostream>

#include "TimeMeasurer.h"

using String = std::string;

class Main
{
public:
    int run();
private:
    static void displayGreeting();
    static void displayMenu();
    void interpretInput();
    void measurements();
    bool keepGoing = true;
    String input;

    TimeMeasurer timeMeasurer;
};


#endif //SDIZO2_MAIN_H
