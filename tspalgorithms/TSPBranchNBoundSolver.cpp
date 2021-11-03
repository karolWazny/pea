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
    unusedNodes = ffqueue<size_t>(inputMatrix.size() + 1);
    currentPath = ffstack<size_t>(inputMatrix.size());
    for(size_t i = 0; i < minOuts.getLength() - 1;){
        minimalValue += minOuts[i++];
        //unusedNodes.pushBack(i);
        unusedNodes.enqueue(i);
    }
    minimalValue += minOuts[minOuts.getLength() - 1];
    currentPath.push(0);
}

void TSPBranchNBoundSolver::solveRecursively(int heuristicSoFar) {
    if(!unusedNodes.getLength()){
        auto totalCostOfCurrentPath = calculateHeuristic(heuristicSoFar, 0);
        if(totalCostOfCurrentPath < solution.totalCost)
            updateSolution(totalCostOfCurrentPath);
    }
    for(size_t i = 0; i < unusedNodes.getLength(); i++){
        //auto currentNode = unusedNodes.removeFirst();
        auto currentNode = unusedNodes.dequeue();
        auto newHeuristic = calculateHeuristic(heuristicSoFar, currentNode);
        if(newHeuristic < solution.totalCost){
            currentPath.push(currentNode);
            solveRecursively(newHeuristic);
            currentPath.pop();
        }
        //unusedNodes.pushBack(currentNode);
        unusedNodes.enqueue(currentNode);
    }
}

int TSPBranchNBoundSolver::calculateHeuristic(int previousHeuristic, size_t nextNode) {
    return previousHeuristic - minOuts[currentPath.getCurrent()] + input->getDistance(currentPath.getCurrent(), nextNode);
}

void TSPBranchNBoundSolver::updateSolution(int cost) {
    solution.totalCost = cost;
    solution.circuit = LinkedList<size_t>();
    auto iterator = currentPath.upwardIterator();
    while(iterator.hasNext()){
        solution.circuit.pushBack(iterator.next());
    }
    solution.circuit.pushBack(0);
}
