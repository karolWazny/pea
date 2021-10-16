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
    for(size_t i = 1; i < size(); i++){
        nodes.pushBack(i);
    }

    currentLevel = Array<Array<PartialSolution>>(1);
    currentLevel[0] = Array<PartialSolution>(size() - 1);
    //mamy jeden pusty zbiór S oraz n - 1 możliwych suffiksów
    for(size_t i = 1; i <= currentLevel[0].getLength(); i++){
        currentLevel[0][i - 1].cost = input->getDistance(0, i);
        currentLevel[0][i - 1].lastNode = i;
    }
}

TSPSolution TSPDynamicProgrammingSolver::solveIteratively() {

    for(currentLevelIndex = 1; currentLevelIndex < size(); currentLevelIndex++){
        iterationOnLevel();
    }
    return {};
}

void TSPDynamicProgrammingSolver::iterationOnLevel() {
    updateMembersForCurrentLevel();

    for(currentSetIndex = 0; currentSetIndex < previousLevel.getLength(); currentSetIndex++){
        iterationForCurrentSet();
    }
}

void TSPDynamicProgrammingSolver::iterationForCurrentSet() {
    for(size_t i = 0; i < previousLevel[currentSetIndex].getLength(); i++){
        //dla danego zbioru S (uporządkowanego) i węzła x nienależącego
        // do tego zbioru tworzymy zbiór S' jako S + {x},
        // następnie tworzymy wszystkie możliwe g(S', x)

        //tworzymy alias dla previousLevel[index][i], żeby było wygodniej pracować
        auto& set = previousLevel[currentSetIndex][i];
        set.circuit.pushBack(set.lastNode);
        set.nodesUsed.put(set.lastNode);

        // przyporządkowujemy jednoznaczny identyfikator zbiorowi S
        //jednocześnie tworząc listę węzłów nieużytych w tym zbiorze
        LinkedList<size_t> unusedNodes;
        size_t setIdentifier{};
        size_t numberOfHits{};
        //todo nie jestem pewien tych przypisań do n i k
        const auto n = size() - 1;
        const auto k = set.circuit.getLength();
        for(size_t j = 1; j < size(); j++){
            if(set.nodesUsed.contains(j)){
                setIdentifier += math::newton(n - j, k - numberOfHits);
                numberOfHits++;
            } else {
                unusedNodes.pushBack(j);
            }
        }
        auto iterator = unusedNodes.iterator();
        for(size_t j = 0; iterator.hasNext(); j++){
            //aliasujemy najlepszą w tym momencie permutację
            //dla tego zbioru i z tym samym węzłem na końcu
            auto& currentlyBestPermutation = currentLevel[setIdentifier][j];
            //
        }
    }
}

void TSPDynamicProgrammingSolver::updateMembersForCurrentLevel() {
    previousLevel = currentLevel;
    currentLevel = Array<Array<PartialSolution>>(math::newton(size() - 1, currentLevelIndex));
    for(size_t j = 0; j < currentLevel.getLength(); j++){
        currentLevel[j] = Array<PartialSolution>(size() - currentLevelIndex - 1);
    }
}
