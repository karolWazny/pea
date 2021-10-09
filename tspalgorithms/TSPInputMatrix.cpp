#include "TSPInputMatrix.h"

#include <utility>
#include <memory>

TSPInputMatrix matrixFrom(std::shared_ptr<int32_t[]> valuesFromFile){
    auto builder = TSPInputMatrix::builder(valuesFromFile[0]);
    auto size = valuesFromFile[0];
    for(size_t from = 0; from < size; from++){
        for(size_t to = 0; to < size; to++) {
            builder.setDistance(from, to, valuesFromFile[from * size + to + 1]);
        }
    }
    return builder.build();
}

TSPInputMatrix::TSPInputMatrix(Array<Array<int>> values) : _values(std::move(values)) {

}

TSPInputMatrix::Builder TSPInputMatrix::builder(size_t nodes) {
    return Builder(nodes);
}

int TSPInputMatrix::getDistance(size_t from, size_t to) const {
    if(from == to)
        return 0;
    return _values[from][to];
}

size_t TSPInputMatrix::size() const{
    return _values.getLength();
}

TSPInputMatrix TSPInputMatrix::Builder::build() {
    return TSPInputMatrix(values);
}

TSPInputMatrix::Builder::Builder(size_t numberOfNodes) {
    values = Array<Array<int>>(numberOfNodes);
    for(size_t i = 0; i < numberOfNodes; i++){
        values[i] = Array<int>(numberOfNodes);
        for(int j = 0; j < numberOfNodes; j++){
            values[i][j] = INT32_MAX;
        }
    }
}

void TSPInputMatrix::Builder::setDistance(size_t from, size_t to, int distance) {
    values[from][to] = distance;
}
