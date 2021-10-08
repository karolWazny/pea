#include "Main.h"

int Main::run() {
    displayGreeting();
    while(keepGoing)
    {
        displayMenu();
        std::getline(std::cin, input);
        interpretInput();
    }
    return 0;
}

void Main::displayGreeting() {
    std::wcout << "Witamy w programie." << std::endl << std::endl;
}

void Main::displayMenu() {
    String menuText = "1. Brute force (przeglad zupelny).\n";
    menuText += "2. Programowanie dynamiczne.\n"
                "3. Automatyczne pomiary czasu\n";
    menuText += "4. Zakoncz program.\n";
    std::cout << menuText;
}

void Main::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                break;
            case 2:
                break;
            case 3:
                measurements();
                break;
            case 4:
                keepGoing = false;
                break;
            default:
                throw 4;
        }
    } catch (...) {
        std::cout << "Niewlasciwy symbol." << std::endl;
        return;
    }
}

void Main::measurements() {
    //timeMeasurer.runMeasurement();
}
