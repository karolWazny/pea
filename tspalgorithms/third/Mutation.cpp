//
// Created by admin on 30.12.2021.
//

#include "Mutation.h"
#include "../../program/Randomizer.h"
#include "../mathfunctions.h"
#include "../../utils/stringutils.h"

Mutation MutationFactory::createMutation(MutationMethod method) {
    switch(method){
        case MutationMethod::REVERSE:
            return [](Individual& individual){
                static Randomizer rand;
                ffarray<int>& permutation = individual.permutation;
                auto firstIndex = rand.getULong(permutation.getLength() - 1);
                auto secondIndex = rand.getULong(permutation.getLength() - 1);
                if(firstIndex > secondIndex)
                    std::swap(firstIndex, secondIndex);
                while(firstIndex < secondIndex){
                    std::swap(permutation[firstIndex], permutation[secondIndex]);
                    firstIndex++;
                    secondIndex--;
                }
            };
        case MutationMethod::RANDOM:
            return [](Individual& individual){
                static Randomizer rand;
                ffarray<int>& permutation = individual.permutation;
                auto firstIndex = rand.getULong(permutation.getLength() + 1);
                auto secondIndex = rand.getULong(permutation.getLength() + 1);
                if(firstIndex > secondIndex)
                    std::swap(firstIndex, secondIndex);
                math::fisherYatesShuffle(permutation, firstIndex, secondIndex);
            };
        default:
            return [](Individual& individual){};
    }
}

MutationMethod mutationMethodFrom(const std::string& str){
    auto properString = trim_copy(str);
}

MutationMethod mutationMethodFrom(std::istream& stream){
    std::string buffer;
    stream >> buffer;
    return mutationMethodFrom(buffer);
}

std::istream& operator>>(std::istream& stream, MutationMethod& method){
    method = mutationMethodFrom(stream);
    return stream;
}
