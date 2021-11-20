#ifndef PEA_MATHFUNCTIONS_H
#define PEA_MATHFUNCTIONS_H

#include "../program/Randomizer.h"

#include "../structure_templates_lib/OrderedCollection.h"

namespace math {
    unsigned long long newton(unsigned long long n, unsigned long long k);

    template <typename T>
    void fisherYatesShuffle(OrderedCollection<T> &collection) {
        static Randomizer rand;
        for(size_t i = 0; i < collection.getLength() - 1; i++){
            size_t index = rand.getULong(collection.getLength() - i - 1) + i;
            auto buffer = collection[i];
            collection[i] = collection[index];
            collection[index] = buffer;
        }
    }
}

#endif //PEA_MATHFUNCTIONS_H
