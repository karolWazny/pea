#ifndef PEA_TREE_H
#define PEA_TREE_H

template<typename T>
class Tree {
public:
    virtual void put(T) = 0;
    virtual bool contains(T) const = 0;
    virtual bool contains(const Tree&) const = 0;
    virtual bool isContainedIn(const Tree&) const = 0;
};


#endif //PEA_TREE_H
