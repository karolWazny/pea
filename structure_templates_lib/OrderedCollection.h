#ifndef PEA_ORDEREDCOLLECTION_H
#define PEA_ORDEREDCOLLECTION_H

template <typename T>
class OrderedCollection {
public:
    virtual T& operator[](size_t index) const = 0;
    [[nodiscard]] virtual size_t getLength() const = 0;
};

#endif //PEA_ORDEREDCOLLECTION_H
