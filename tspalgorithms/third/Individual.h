#ifndef PEA_INDIVIDUAL_H
#define PEA_INDIVIDUAL_H

#include "../../structure_templates_lib/array_lib/ffarray.h"

class Individual {
public:
    ffarray<int> permutation;
    long long cost{INT64_MAX};

    Individual copy(){
        Individual individual;
        copyTo(individual);
        return individual;
    }

    void copyTo(Individual& individual){
        individual.cost = cost;
        individual.permutation = permutation.copy();
    }
};

#endif //PEA_INDIVIDUAL_H
