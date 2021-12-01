#ifndef SDIZO2_MAIN_H
#define SDIZO2_MAIN_H

#include <string>
#include <iostream>
#include <filesystem>

#include "TimeMeasurer.h"
#include "../tspalgorithms/TSPInputMatrix.h"
#include "../tspalgorithms/TSPAbstractSolver.h"
#include "ProgramSetup.h"
#include "Program.h"
#include "Operations.h"
#include "../tspalgorithms/deterministic/TSPBruteForceSolver.h"
#include "../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"
#include "../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"
#include "../tspalgorithms/stochastic/TSPTabuSearchSolver.h"
#include "../tspalgorithms/stochastic/TSPSimulatedAnnealingSolver.h"

using String = std::string;

class Main : public Program, public Operations
{
public:
    explicit Main(ProgramSetup&);
    int run() override;
    void setFunctions() override{};
private:
    static void displayGreeting();
    static void displayMenu();
    void interpretInput();

    void measurements();
    void readFromFile();
    void displayMatrix();
    void bruteForce();
    void branchAndBound();
    void dynamicProgramming();
    void generateMatrix();
    void solveSA();
    void solveTS();
    void saveMatrix();


    void solve(const std::string& methodName, TSPAbstractSolver& solver);

    bool keepGoing = true;
    String input;
    TSPInputMatrix adjacencyMatrix;

    TimeMeasurer timeMeasurer;

    template <typename T>
    void solveStochasticallyWithParameters(const std::string& methodName,
                                           const std::string& fileName,
                                           typename T::Parameters defaultParams){
        bool readFromFile = false;
        typename T::Parameters params = defaultParams;
        if(std::filesystem::exists(fileName)) {
            std::cout << "Znaleziono plik z parametrami.\nWczytywanie parametrow...\n";
            std::ifstream stream;
            stream.open(fileName);
            try {
                params = T::Parameters::from(stream);
                readFromFile = true;
                std::cout << "Wczytano parametry z pliku.\n";
            } catch (const std::exception& e) {
                std::cout << "Problem z odczytem z pliku." << std::endl;
            }
        }
        if(!readFromFile){
            std::cout << "Generowanie parametrow domyslnych..." << std::endl;
            std::cout << "Tworzenie nowego pliku z konfiguracja..." << std::endl;
            std::ofstream ofstream;
            ofstream.open(fileName);
            ofstream << params.parse();
            std::cout << "Utworzono nowy plik z konfiguracja." << std::endl;
        }
        auto solver = T(params);
        solve("symulowanego wyzarzania",solver);
        std::cout << "Dla nastepujacych wartosci parametrow:" << std::endl;
        std::cout << params.parse() << std::endl;
    };
};


#endif //SDIZO2_MAIN_H
