#include "TSPDynamicProgrammingSolver.h"

TSPSolution TSPDynamicProgrammingSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    prepareMembers(inputMatrix);
    solveIteratively();
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

TSPSolution TSPDynamicProgrammingSolver::solveIteratively() {
    for(size_t i = 1; i < input->size(); i++){
        iterationOnLevel(i);
    }
    return {};
}

void TSPDynamicProgrammingSolver::iterationOnLevel(const size_t i) {
    updateMembersForLevel(i);

    for(size_t j = 0; j < previousLevel.getLength(); j++){
        iterationForSetWithIndex(j);
    }
}

void TSPDynamicProgrammingSolver::iterationForSetWithIndex(const size_t i) {
}

void TSPDynamicProgrammingSolver::updateMembersForLevel(size_t i) {
    previousLevel = currentLevel;
    currentLevel = Array<Array<TSPSolution>>(math::newton(input->size(), i));
    for(size_t j = 0; j < currentLevel.getLength(); j++){
        currentLevel[j] = Array<TSPSolution>(input->size() - i - 1);
    }
}
