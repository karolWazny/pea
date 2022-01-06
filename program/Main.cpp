#include "Main.h"
#include "file/TxtFileHandler.h"
#include "../tspalgorithms/third/GeneticSolver.h"
#include "measurements/GAMeasurements.h"
#include "measurements/SAMeasurements.h"
#include <filesystem>

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

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
                "8. Symulowane wyzarzanie\n"
                "9. Tabu search\n"
                "10. Algorytm ewolucyjny\n";
    menuText += "11. Zakoncz program.\n"
                "100. Zapisz graf do pliku\n\n";
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
                solveGenetic();
                break;
            case 11:
                keepGoing = false;
                break;
            case 100:
                saveMatrix();
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
        //timeMeasurer.runMeasurement();
        //GAMeasurements meas;
        SAMeasurements meas;
        meas.runParametrizedMeasurement();
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

    std::string atspSuffix = ".atsp";
    std::string txtSuffix = ".txt";

    std::shared_ptr<int[]> fileContent;

    if(hasEnding(filename, atspSuffix)){
        fileContent = AtspFileHandler().fromFile(filename);
    } else if(hasEnding(filename, txtSuffix)) {
        fileContent = TxtFileHandler().fromFile(filename);
    } else {
        std::cout << "Nieznane rozszerzenie pliku.\n"
                     "Dopuszczalne rozszerzenia: .atsp i .txt.\n";
        return;
    }
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
    auto stopWatch = StopWatch();
    stopWatch.start();
    auto result = solver.solveFor(adjacencyMatrix);
    stopWatch.stop();
    std::cout << "Uzyskany wynik:\n\tKoszt minimalnego cyklu: " << std::to_string(result.totalCost) << std::endl;
    std::cout << "\tMinimalny cykl: " << result.circuit.toString() << std::endl
                    << "\tRozmiar instancji (N): " << std::to_string(adjacencyMatrix.size()) << std::endl
                    << "\tCzas: " << std::to_string(stopWatch.getLastMeasurementsFloat() / 100000) << " s" << std::endl
                    << std::endl;
}

void Main::generateMatrix() {
    std::cout << "How big'a matrix do you want?\n";
    adjacencyMatrix = randomMatrix(readInt());
    std::cout << "Matrix has been generated.\nMatrix has you.\n";
    displayMatrix();
}

void Main::solveSA() {
    solveStochasticallyWithParameters
            <TSPSimulatedAnnealingSolver>
            ("symulowanego wyzarzania",
             "saparams.txt",
             TSPSimulatedAnnealingSolver::Parameters(
                     100.0, 0.9,
                     adjacencyMatrix.size() * adjacencyMatrix.size() * 0.2,
                     1, 8));
}

void Main::solveTS() {
    solveStochasticallyWithParameters
            <TSPTabuSearchSolver>
            ("Tabu Search",
             "tsparams.txt",
             TSPTabuSearchSolver::Parameters(
                     3 * adjacencyMatrix.size(),
                     8));
}

void Main::saveMatrix() {
    std::cout << "Podaj nazwe pliku: ";
    auto filename = readStr();

    std::string atspSuffix = ".atsp";
    std::string txtSuffix = ".txt";

    if(hasEnding(filename, atspSuffix)){
        AtspFileHandler().toFile(adjacencyMatrix, filename);
    } else if(hasEnding(filename, txtSuffix)) {
        TxtFileHandler().toFile(adjacencyMatrix, filename);
    } else {
        std::cout << "Nieznane rozszerzenie pliku.\n"
                     "Dopuszczalne rozszerzenia: .atsp i .txt.\n";
        return;
    }
    std::cout << "Zapisano plik poprawnie pod nazwa " << filename << "." << std::endl << std::endl;
}

void Main::solveGenetic() {
    solveStochasticallyWithParameters
            <GeneticSolver>
            ("algorytmu ewolucyjnego",
             "gaparams.txt",
             GeneticSolver::Parameters());
}
