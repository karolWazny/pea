#include "Main.h"
#include <filesystem>

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
    String menuText = "1. Wczytaj graf z pliku\n"
                      "2. Wyswietl macierz sasiedztwa aktualnego grafu\n"
                      "3. Brute force (przeglad zupelny).\n";
    menuText += "4. Programowanie dynamiczne.\n"
                "5. Metoda podzialu i ograniczen\n"
                "6. Automatyczne pomiary czasu\n";
    menuText += "7. Zakoncz program.\n";
    std::cout << menuText;
}

void Main::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                readFromFile();
                break;
            case 2:
                displayMatrix();
                break;
            case 3:
                bruteForce();
                break;
            case 4:
                dynamicProgramming();
                break;
            case 5:
                measurements();
                break;
            case 6:
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
    std::cout << "Ta funkcjonalnosc wkrotce sie pojawi...\n";
}

Main::Main(ProgramSetup & setup) : adjacencyMatrix(0) {
    setup.setup(*this);
}

void Main::readFromFile() {
    std::cout << "Podaj nazwe pliku: ";
    auto filename = readStr();
    if(!std::filesystem::exists(filename)){
        std::cout << "Nie mozna znalezc podanego pliku.\n"
                     "Sprawdz poprawnosc sciezki i sprobuj jeszcze raz.\n";
        return;
    }
    auto fileContent = TextFileReader().fromFile(filename);
    adjacencyMatrix = TSPInputMatrix::from(fileContent);
    std::cout<< "Udalo sie wczytac macierz sasiedztwa z pliku.\n\n";
}

void Main::displayMatrix() {
    std::cout << adjacencyMatrix.representation();
}

void Main::bruteForce() {
    std::cout << "Znajdowanie minimalnego cyklu Hamiltona metoda"
                 "\nprzegladu zupelnego. Prosze czekac...\n";
    auto result = TSPBruteForceSolver().solveFor(adjacencyMatrix);
    std::cout << "Uzyskany wynik:\nKoszt minimalnego cyklu: " << std::to_string(result.totalCost) << std::endl;
    std::cout << "Minimalny cykl: " << result.circuit.toString() << std::endl << std::endl;
}

void Main::branchAndBound() {
    std::cout << "Ta funkcjonalnosc wkrotce sie pojawi...\n";
}

void Main::dynamicProgramming() {
    std::cout << "Ta funkcjonalnosc wkrotce sie pojawi...\n";
}
