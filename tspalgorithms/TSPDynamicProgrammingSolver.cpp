#include "TSPDynamicProgrammingSolver.h"

TSPSolution TSPDynamicProgrammingSolver::solveFor(const TSPInputMatrix &inputMatrix) {
    prepareMembers(inputMatrix);
    return solveIteratively();
}

void TSPDynamicProgrammingSolver::prepareMembers(const TSPInputMatrix &inputMatrix) {
    this->input = &inputMatrix;

    currentLevel = ffarray<ffarray<PartialSolution>>(1);
    currentLevel[0] = ffarray<PartialSolution>(size() - 1);
    //mamy jeden pusty zbiór S oraz n - 1 możliwych suffiksów
    for(size_t i = 1; i <= currentLevel[0].getLength(); i++){
        currentLevel[0][i - 1].cost = input->getDistance(0, i);
        currentLevel[0][i - 1].lastNode = i;
    }
}

TSPSolution TSPDynamicProgrammingSolver::solveIteratively() {

    for(currentLevelIndex = 1; currentLevelIndex < size() - 1; currentLevelIndex++){
        iterationOnLevel();
    }
    TSPSolution solution;
    for(size_t i = 0; i < currentLevel.getLength(); i++){
        auto& currentSolution = currentLevel[i][0];
        const auto cost = currentSolution.cost + input->getDistance(currentSolution.lastNode, 0);
        if(cost < solution.totalCost){
            solution.totalCost = cost;
            solution.circuit = currentSolution.circuit;
            solution.circuit.pushFront(0);
            solution.circuit.pushBack(currentSolution.lastNode);
            solution.circuit.pushBack(0);
        }
    }
    return solution;
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
            auto currentLastNode = iterator.next();
            auto& currentlyBestPermutation = currentLevel[setIdentifier][j];
            int32_t candidateCost = set.cost + input->getDistance(set.lastNode, currentLastNode);
            if(candidateCost < 0)
                candidateCost = INT32_MAX;
            if(currentlyBestPermutation.cost > candidateCost){
                //update currentlyBestPermutation:
                //copy circuit and element-by-element,
                auto innerIterator = set.circuit.iterator();
                currentlyBestPermutation.circuit = LinkedList<size_t>();
                while(innerIterator.hasNext()){
                    currentlyBestPermutation.circuit.pushBack(innerIterator.next());
                }
                //copy tree only if this is the first permutation found!!!
                //update last node (in case this is the first permutation found)
                if(!currentlyBestPermutation.lastNode){
                    currentlyBestPermutation.lastNode = currentLastNode;
                    set.nodesUsed.copyTo(currentlyBestPermutation.nodesUsed);
                }
                //update cost (of course)
                currentlyBestPermutation.cost = candidateCost;
            }
        }
    }
}

void TSPDynamicProgrammingSolver::updateMembersForCurrentLevel() {
    previousLevel = currentLevel;
    currentLevel = ffarray<ffarray<PartialSolution>>(math::newton(size() - 1, currentLevelIndex));
    for(size_t j = 0; j < currentLevel.getLength(); j++){
        currentLevel[j] = ffarray<PartialSolution>(size() - currentLevelIndex - 1);
    }
}
