#include "TSPBranchNBoundSolver.h"

TSPSolution TSPBranchNBoundSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    prepareMembers(inputMatrix);
    solveRecursively(minimalValue);
    return solution;
}

void TSPBranchNBoundSolver::prepareMembers(const TSPInputMatrix &inputMatrix) {
    input = &inputMatrix;
    minOuts = input->minimalOuts();
    solution = TSPSolution();
    minimalValue = 0;
    unusedNodes = LinkedList<size_t>();
    currentPath = LinkedList<size_t>();
    for(size_t i = 0; i < minOuts.getLength();){
        minimalValue += minOuts[i++];
        unusedNodes.pushBack(i);
    }
    unusedNodes.removeLast();
    currentPath.pushBack(0);
}

void TSPBranchNBoundSolver::solveRecursively(int heuristicSoFar) {
    if(!unusedNodes.getLength()){
        auto totalCostOfCurrentPath = calculateHeuristic(heuristicSoFar, 0);
        if(totalCostOfCurrentPath < solution.totalCost)
            updateSolution(totalCostOfCurrentPath);
    }
    for(size_t i = 0; i < unusedNodes.getLength(); i++){
        auto currentNode = unusedNodes.removeFirst();
        auto newHeuristic = calculateHeuristic(heuristicSoFar, currentNode);
        if(newHeuristic < solution.totalCost){
            currentPath.pushBack(currentNode);
            solveRecursively(newHeuristic);
            currentPath.removeLast();
        }
        unusedNodes.pushBack(currentNode);
    }
}

int TSPBranchNBoundSolver::calculateHeuristic(int previousHeuristic, size_t nextNode) {
    return previousHeuristic - minOuts[currentPath.getLast()] + input->getDistance(currentPath.getLast(), nextNode);
}

void TSPBranchNBoundSolver::updateSolution(int cost) {
    solution.totalCost = cost;
    solution.circuit = LinkedList<size_t>();
    auto iterator = currentPath.iterator();
    while(iterator.hasNext()){
        solution.circuit.pushBack(iterator.next());
    }
    solution.circuit.pushBack(0);
}
