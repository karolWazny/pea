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
    String menuText = "1. Automatyczne pomiary czasu\n"
                      "2. Wczytaj graf z pliku\n"
                      "3. Generuj losowy graf\n"
                      "4. Wyswietl macierz sasiedztwa aktualnego grafu\n"
                      "5. Brute force (przeglad zupelny).\n";
    menuText += "6. Programowanie dynamiczne.\n"
                "7. Metoda podzialu i ograniczen\n"
                "8. Symulowane wyżarzanie\n"
                "9. Tabu search\n";
    menuText += "10. Zakoncz program.\n";
    std::cout << menuText;
}

void Main::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                measurements();
                break;
            case 2:
                readFromFile();
                break;
            case 3:
                generateMatrix();
                break;
            case 4:
                displayMatrix();
                break;
            case 5:
                bruteForce();
                break;
            case 6:
                dynamicProgramming();
                break;
            case 7:
                branchAndBound();
                break;
            case 8:
                solveSA();
                break;
            case 9:
                solveTS();
                break;
            case 10:
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
    try{
        timeMeasurer.runMeasurement();
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

Main::Main(ProgramSetup & setup) {
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
    auto solver = TSPBruteForceSolver();
    solve("przegladu zupelnego", solver);
}

void Main::branchAndBound() {

    auto solver = TSPBranchNBoundSolver();
    solve("podzialu i ograniczen", solver);
}

void Main::dynamicProgramming() {

    auto solver = TSPDynamicProgrammingSolver();
    solve("programowania dynamicznego", solver);
}

void Main::solve(const std::string& methodName, TSPAbstractSolver &solver) {
    std::cout << "Znajdowanie minimalnego cyklu Hamiltona metoda\n" << methodName
                        << ". Prosze czekac...\n";
    auto result = solver.solveFor(adjacencyMatrix);
    std::cout << "Uzyskany wynik:\nKoszt minimalnego cyklu: " << std::to_string(result.totalCost) << std::endl;
    std::cout << "Minimalny cykl: " << result.circuit.toString() << std::endl << std::endl;
}

void Main::generateMatrix() {
    std::cout << "How big'a matrix do you want?\n";
    adjacencyMatrix = randomMatrix(readInt());
    std::cout << "Matrix has been generated.\nMatrix has you.\n";
    displayMatrix();
}

void Main::solveSA() {

}

void Main::solveTS() {

}
