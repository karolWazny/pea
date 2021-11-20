#ifndef PEA_REALRANDOM_H
#define PEA_REALRANDOM_H


#include <random>

template <typename T>
class RealRandom {
public:
    explicit RealRandom(T lowerBound = 0.0,
               double upperBound = 1.0)
               : lowerBound(lowerBound),
               upperBound(upperBound),
               generator(std::random_device(std::random_device())()),
               distribution(lowerBound, upperBound){
    }

    [[nodiscard]] T getLowerBound() const {
        return lowerBound;
    }

    [[nodiscard]] T getUpperBound() const {
        return upperBound;
    };

    double operator()(){
        return distribution(generator);
    };
private:
    const T lowerBound;
    const T upperBound;

    std::uniform_real_distribution<T> distribution;
    std::mt19937 generator;
};


#endif //PEA_REALRANDOM_H
