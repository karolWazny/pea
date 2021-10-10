#include "TSPBruteForceSolver.h"

TSPSolution TSPBruteForceSolver::solveFor(const TSPInputMatrix &input) {
    this->inputMatrix = &input;
    unusedNodes = LinkedList<size_t>();
    for(size_t i = 1; i < input.size(); i++) {
        unusedNodes.pushBack(i);
    }
    currentBranch = LinkedList<size_t>();
    currentBranch.pushBack(0);
    solution = TSPSolution();

    goDeeper();

    return solution;
}

void TSPBruteForceSolver::goDeeper() {
    if(unusedNodes.isEmpty()) {
        compareAndUpdateBestPath();
        return;
    }

    for(size_t i = 0; i < unusedNodes.getLength(); i++) {
        auto currentElement = unusedNodes.removeFirst();
        currentBranch.pushBack(currentElement);

        goDeeper();

        currentBranch.removeLast();
        unusedNodes.pushBack(currentElement);
    }
}

void TSPBruteForceSolver::compareAndUpdateBestPath() {
    int currentSum{};

    auto iterator = currentBranch.iterator();
    auto from = iterator.next();
    auto to = from;
    while (iterator.hasNext()){
        from = to;
        to = iterator.next();
        currentSum += inputMatrix->getDistance(from, to);
    }
    currentSum += inputMatrix->getDistance(to, 0);
    if(currentSum < solution.totalCost){
        solution.totalCost = currentSum;
        iterator = currentBranch.iterator();
        solution.circuit = LinkedList<size_t>();
        while(iterator.hasNext()){
            solution.circuit.pushBack(iterator.next());
        }
        solution.circuit.pushBack(0);
    }
}
