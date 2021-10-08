#ifndef PEA_TSPINPUTMATRIX_H
#define PEA_TSPINPUTMATRIX_H

#include "../structure_templates_lib/structures.h"

class TSPInputMatrix {
public:
    class Builder;
    static TSPInputMatrix::Builder builder(size_t nodes);
    int getDistance(size_t from, size_t to);

private:
    explicit TSPInputMatrix(Array<Array<int>>);

    Array<Array<int>> _values;
};

class TSPInputMatrix::Builder {
public:
    TSPInputMatrix build();
    explicit Builder(size_t);
    void setDistance(size_t from, size_t to, int distance);

private:
    Array<Array<int>> values;
};

#endif //PEA_TSPINPUTMATRIX_H
