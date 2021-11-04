#include "TSPBruteForceSolver.h"

TSPSolution TSPBruteForceSolver::solveFor(const TSPInputMatrix &input) {
    allNodes = new size_t[input.size() - 1];

    for(size_t i = 0; i < input.size() - 1; i++){
        allNodes[i] = i + 1;
    }

    this->inputMatrix = &input;

    do {
        compareCurrentPermutation();
    } while(nextPermutation());

    delete allNodes;
    return solution;
}

bool TSPBruteForceSolver::nextPermutation() {
    size_t first = 0;
    size_t last = inputMatrix->size() - 2;
    auto index = last;
    while(true){
        size_t index1, index2;

        index1 = index;
        if(allNodes[--index] < allNodes[index1]) {
            index2 = last;
            while (allNodes[index] >= allNodes[index2]) {
                index2--;
            }
            {
                auto buffer = allNodes[index];
                allNodes[index] = allNodes[index2];
                allNodes[index2] = buffer;
            }

            //reverse items from index1 to last

            for(auto last = inputMatrix->size() - 2; last > index1; index1++, last--){
                auto buffer = allNodes[index1];
                allNodes[index1] = allNodes[last];
                allNodes[last] = buffer;
            }

            return true;
        }

        if(index == 0){
            for(size_t last = inputMatrix->size() - 2, first = 0; last > first; first++, last--){
                auto buffer = allNodes[first];
                allNodes[first] = allNodes[last];
                allNodes[last] = buffer;
            }
            return false;
        }
    }
}

void TSPBruteForceSolver::compareCurrentPermutation() {
    size_t previous = 0;
    size_t next = 0;
    int cost{};
    for(size_t i = 0; i < inputMatrix->size() - 1; i++){
        next = allNodes[i];
        cost+= inputMatrix->getDistance(previous, next);
        previous = next;
    }
    cost += inputMatrix->getDistance(previous, 0);
    if(cost < solution.totalCost){
        solution.totalCost = cost;
        solution.circuit = LinkedList<size_t>();
        solution.circuit.pushBack(0);
        for(size_t i = 0; i < inputMatrix->size() - 1; i++){
            solution.circuit.pushBack(allNodes[i]);
        }
        solution.circuit.pushBack(0);
    }
}
