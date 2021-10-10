#include "TSPDynamicProgrammingSolver.h"

TSPSolution TSPDynamicProgrammingSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    prepareMembers(inputMatrix);
    return solveRecursively(0);
}

TSPSolution TSPDynamicProgrammingSolver::solveRecursively(size_t node) {
    if(nodes.isEmpty())
        return recursionEdge(node);

    auto partialSolution = TSPSolution();
    for(size_t i = 0; i < nodes.getLength(); i++){
        auto currentNode = nodes.removeFirst();
        auto currentPartialSolution = solveRecursively(currentNode);

        if(partialSolution.totalCost > currentPartialSolution.totalCost + input->getDistance(currentNode, node)){
            partialSolution = currentPartialSolution;
            partialSolution.totalCost += input->getDistance(currentNode, node);
        }

        nodes.pushBack(currentNode);
    }

    partialSolution.circuit.pushBack(node);
    return partialSolution;
}

TSPSolution TSPDynamicProgrammingSolver::recursionEdge(size_t node) {
    auto partialSolution = TSPSolution();
    partialSolution.circuit.pushBack(0);
    partialSolution.circuit.pushBack(node);
    partialSolution.totalCost = input->getDistance(0, node);
    return partialSolution;
}

void TSPDynamicProgrammingSolver::prepareMembers(const TSPInputMatrix &inputMatrix) {
    nodes = LinkedList<size_t>();
    this->input = &inputMatrix;
    for(size_t i = 1; i < input->size(); i++){
        nodes.pushBack(i);
    }
}
