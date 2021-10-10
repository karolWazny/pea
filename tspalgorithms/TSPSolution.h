#ifndef PEA_TSPSOLUTION_H
#define PEA_TSPSOLUTION_H

#include "../structure_templates_lib/structures.h"

class TSPSolution {
public:
    LinkedList<size_t> circuit;
    int totalCost{INT32_MAX};
};


#endif //PEA_TSPSOLUTION_H
