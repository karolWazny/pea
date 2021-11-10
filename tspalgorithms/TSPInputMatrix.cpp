#include "TSPInputMatrix.h"

#include <utility>
#include <memory>
#include <sstream>
#include <iomanip>
#include "../program/Randomizer.h"
#include "PlanarVector.h"

TSPInputMatrix matrixFrom(std::shared_ptr<int32_t[]> valuesFromFile){
    return TSPInputMatrix::from(valuesFromFile);
}

TSPInputMatrix::TSPInputMatrix(ffarray<ffarray<int>> values) : _values(std::move(values)) {

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

Array<int> TSPInputMatrix::minimalOuts() const {
    Array<int> outs(size());
    for(size_t i = 0; i < outs.getLength(); i++){
        outs[i] = INT32_MAX;
        for(size_t j = 0; j < size(); j++){
            if(outs[i] > _values[i][j] && i != j)
                outs[i] = _values[i][j];
        }
    }
    return outs;
}

TSPInputMatrix TSPInputMatrix::from(std::shared_ptr<int32_t[]> valuesFromFile) {
    auto builder = TSPInputMatrix::builder(valuesFromFile[0]);
    auto size = valuesFromFile[0];
    for(size_t from = 0; from < size; from++){
        for(size_t to = 0; to < size; to++) {
            builder.setDistance(from, to, valuesFromFile[from * size + to + 1]);
        }
    }
    return builder.build();
}

std::string TSPInputMatrix::representation() const {
    std::ostringstream stringStream;
    stringStream << std::right << std::setw(6) <<"|";
    for(size_t i = 0; i < size(); i++){
        stringStream << std::right << std::setw(5)<<std::to_string(i);
    }
    stringStream << std::endl << std::string(5, '-') << "+" << std::string(size() * 5, '-') << std::endl;
    for(size_t i = 0; i < size(); i++){
        stringStream << std::right << std::setw(5) << std::to_string(i) << "|";
        for(size_t j = 0; j < size(); j++){
            if(i != j)
                stringStream << std::right << std::setw(5) << std::to_string(_values[i][j]);
            else
                stringStream << std::right << std::setw(5) << '-';
        }
        stringStream << std::endl;
    }
    return stringStream.str();
}

TSPInputMatrix TSPInputMatrix::Builder::build() {
    return TSPInputMatrix(values);
}

TSPInputMatrix::Builder::Builder(size_t numberOfNodes) {
    values = ffarray<ffarray<int>>(numberOfNodes);
    for(size_t i = 0; i < numberOfNodes; i++){
        values[i] = ffarray<int>(numberOfNodes);
        for(int j = 0; j < numberOfNodes; j++){
            values[i][j] = INT32_MAX;
        }
    }
}

void TSPInputMatrix::Builder::setDistance(size_t from, size_t to, int distance) {
    values[from][to] = distance;
}

TSPInputMatrix randomMatrix(size_t size){
    Randomizer randomizer;
    auto points = ffarray<PlanarVector>(size);
    for(size_t i = 0; i < size; i++){
        points[i].setX(randomizer.getInt(300));
        points[i].setY(randomizer.getInt(300));
    }

    auto values = std::shared_ptr<int32_t[]>(new int32_t[size * size + 1]);
    values[0] = size;

    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            double distance = (points[i] - points[j]).getModulus();
            values[i * size + j + 1] = std::lround(distance);
        }
    }

    for(int i = 0; i < size; i++){
        values[i * size + i + 1] = INT32_MAX;
    }
    return TSPInputMatrix::from(values);
}
