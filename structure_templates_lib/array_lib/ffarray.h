#ifndef PEA_FFARRAY_H
#define PEA_FFARRAY_H

#include <vector>

template <typename T>
class ffarray{
public:
    explicit ffarray(size_t demandedSize) : size(demandedSize){
        if(demandedSize)
            table = new T[demandedSize];
        else
            table = nullptr;
        elementsShared = std::shared_ptr<T[]>(table);
    };
    ffarray() : size(0), table(nullptr), elementsShared(nullptr){};
    T& operator[](size_t index) const{
        return table[index];
    };

    [[nodiscard]] size_t getLength() const {
        return size;
    };
private:
    std::shared_ptr<T[]> elementsShared;
    T* table;
    size_t size;
};

#endif //PEA_FFARRAY_H
