#ifndef SDIZO_1_CONSEQUENTLIBERATOR_H
#define SDIZO_1_CONSEQUENTLIBERATOR_H

#include "../nodes/Node.h"
#include "NodeUtility.h"
#include "Side.h"


template <typename T>
class ConsequentLiberator : public NodeUtility<T>
{
public:
    explicit ConsequentLiberator(NodePointer<T> root);
    void free(NodePointer<T> node);
    NodePointer<T> getFreed();
private:
    NodePointer<T> nodeToFree;
};

template<typename T>
ConsequentLiberator<T>::ConsequentLiberator(NodePointer<T> root) {
    NodeUtility<T>::currentNode = root;
}

template<typename T>
void ConsequentLiberator<T>::free(NodePointer<T> node){
    nodeToFree = node;
    auto parent = nodeToFree->getParent();
    auto child = nodeToFree->getRight();
    child->setParent(parent);
    parent->setLeft(child);
}

template<typename T>
NodePointer<T> ConsequentLiberator<T>::getFreed() {
    return nodeToFree;
}

#endif //SDIZO_1_CONSEQUENTLIBERATOR_H
