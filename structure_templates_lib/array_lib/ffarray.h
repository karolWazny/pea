#ifndef PEA_FFARRAY_H
#define PEA_FFARRAY_H

#include <vector>
#include "../OrderedCollection.h"

template <typename T>
class ffarray : public OrderedCollection<T> {
public:
    explicit ffarray(size_t demandedSize) : size(demandedSize){
        if(demandedSize)
            table = new T[demandedSize];
        else
            table = nullptr;
        elementsShared = std::shared_ptr<T[]>(table);
    };
    ffarray() : size(0), table(nullptr), elementsShared(nullptr){};
    T& operator[](size_t index) const override {
        return table[index];
    };

    [[nodiscard]] size_t getLength() const override {
        return size;
    }

    ffarray<T> copy(){
        ffarray<T> output(size);
        for(size_t i = 0; i < size; i++){
            output[i] = table[i];
        }
        return output;
    };
private:
    std::shared_ptr<T[]> elementsShared;
    T* table;
    size_t size;
};

#endif //PEA_FFARRAY_H
