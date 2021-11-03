#ifndef PEA_TSPINPUTMATRIX_H
#define PEA_TSPINPUTMATRIX_H

#include "../structure_templates_lib/structures.h"

class TSPInputMatrix {
public:
    explicit TSPInputMatrix(ffarray<ffarray<int>>);
    TSPInputMatrix() = default;
    class Builder;
    static TSPInputMatrix::Builder builder(size_t nodes);
    [[nodiscard]] int getDistance(size_t from, size_t to) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] Array<int> minimalOuts() const;
    [[nodiscard]] std::string representation() const;

    static TSPInputMatrix from(std::shared_ptr<int32_t[]> valuesFromFile);

private:
    ffarray<ffarray<int>> _values;
};

class TSPInputMatrix::Builder {
public:
    TSPInputMatrix build();
    explicit Builder(size_t);
    void setDistance(size_t from, size_t to, int distance);

private:
    ffarray<ffarray<int>> values{};
};

TSPInputMatrix matrixFrom(std::shared_ptr<int32_t[]> valuesFromFile);

TSPInputMatrix randomMatrix(size_t size);

#endif //PEA_TSPINPUTMATRIX_H
