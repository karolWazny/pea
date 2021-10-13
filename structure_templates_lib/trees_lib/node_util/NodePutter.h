#ifndef SDIZO_1_NODEPUTTER_H
#define SDIZO_1_NODEPUTTER_H

#include "../nodes/Node.h"
#include "PlaceToPutFinder.h"
#include "../nodes/SimpleFactory.h"
#include "../nodes/NodeFactory.h"
#include "NodeUtility.h"

template <typename T>
class NodePutter : public NodeUtility<T>
{
public:
    explicit NodePutter(NodePointer<T> root, NodeFactory<T>* nodeFactory);
    explicit NodePutter(NodePointer<T> root);
    void put(T);
    NodePointer<T> getFreshNode();
private:
    NodePointer<T> root;
    NodePointer<T> freshNode;
    Side sideOfPlaceToPut;
    std::unique_ptr<NodeFactory<T>> factory;
};

template<typename T>
NodePutter<T>::NodePutter(NodePointer<T> root, NodeFactory<T>* nodeFactory) {
    this->root = root;
    this->factory = std::unique_ptr<NodeFactory<T>>(nodeFactory);
}


template<typename T>
NodePutter<T>::NodePutter(NodePointer<T> root) {
    this->root = root;
    this->factory = std::unique_ptr<NodeFactory<T>>(new SimpleFactory<T>());
}

template<typename T>
void NodePutter<T>::put(T key) {
    currentNode = root;
    auto finder = PlaceToPutFinder<T>(root);
    finder.setKeyToBePut(key);
    finder.find();
    sideOfPlaceToPut = finder.getPlaceSide();
    currentNode = finder.getFound();
    freshNode = factory->createNode(key);
    currentNode->setSide(freshNode, sideOfPlaceToPut);
    if(!currentNode->isNil())
        freshNode->setParent(currentNode);
    currentNode = freshNode;
}

template<typename T>
NodePointer<T> NodePutter<T>::getFreshNode() {
    return freshNode;
}


#endif //SDIZO_1_NODEPUTTER_H
