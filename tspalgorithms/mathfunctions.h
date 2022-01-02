#ifndef PEA_MATHFUNCTIONS_H
#define PEA_MATHFUNCTIONS_H

#include "../program/Randomizer.h"

#include "../structure_templates_lib/OrderedCollection.h"

namespace math {
    unsigned long long newton(unsigned long long n, unsigned long long k);

    template <typename T>
    void fisherYatesShuffle(OrderedCollection<T> &collection, long long firstIndex, long long secondIndex) {
        static Randomizer rand;
        for(long long i = firstIndex; i < secondIndex - 1; i++){
            size_t index = rand.getULong(collection.getLength() - i - 1) + i;
            std::swap(collection[i], collection[index]);
        }
    }

    template <typename T>
    void fisherYatesShuffle(OrderedCollection<T> &collection) {
        fisherYatesShuffle(collection, 0, collection.getLength());
    }

    template <typename T>
    void heapSort(OrderedCollection<T> &collection) {
        for(size_t i = 1; i < collection.getLength(); i++){
            auto index = i;
            while(index){
                auto parentIndex = (index - 1) >> 1;
                if(collection[index] < collection[parentIndex])
                    break;
                std::swap(collection[index], collection[parentIndex]);
                index = parentIndex;
            }
        }

        for(auto i = collection.getLength() - 1; i; i--){
            std::swap(collection[0], collection[i]);
            auto index = 0;
            auto child = (index << 1) + 1;
            while(child < i) {
                if(child + 1 < i){
                    child = (collection[child] > collection[child + 1] ? child : child + 1);
                }
                if(collection[index] < collection[child]){
                    std::swap(collection[index], collection[child]);
                    index = child;
                    child = (index << 1) + 1;
                } else
                    break;
            }
        }
    }
}

#endif //PEA_MATHFUNCTIONS_H
