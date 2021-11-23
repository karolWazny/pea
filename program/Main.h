#ifndef SDIZO2_MAIN_H
#define SDIZO2_MAIN_H

#include <string>
#include <iostream>

#include "TimeMeasurer.h"
#include "../tspalgorithms/TSPInputMatrix.h"
#include "../tspalgorithms/TSPAbstractSolver.h"
#include "ProgramSetup.h"
#include "Program.h"
#include "Operations.h"
#include "../tspalgorithms/deterministic/TSPBruteForceSolver.h"
#include "../tspalgorithms/deterministic/TSPBranchNBoundSolver.h"
#include "../tspalgorithms/deterministic/TSPDynamicProgrammingSolver.h"

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

    void solve(const std::string& methodName, TSPAbstractSolver& solver);

    bool keepGoing = true;
    String input;
    TSPInputMatrix adjacencyMatrix;

    TimeMeasurer timeMeasurer;

};


#endif //SDIZO2_MAIN_H
