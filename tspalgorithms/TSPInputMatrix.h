#ifndef PEA_TSPINPUTMATRIX_H
#define PEA_TSPINPUTMATRIX_H

#include "../structure_templates_lib/structures.h"

class TSPInputMatrix {
public:
    class Builder;
    static TSPInputMatrix::Builder builder(size_t nodes);
    [[nodiscard]] int getDistance(size_t from, size_t to) const;
    [[nodiscard]] size_t size() const;
    explicit TSPInputMatrix(Array<Array<int>>);
    [[nodiscard]] Array<int> minimalOuts() const;

private:
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

TSPInputMatrix matrixFrom(std::shared_ptr<int32_t[]> valuesFromFile);

#endif //PEA_TSPINPUTMATRIX_H
