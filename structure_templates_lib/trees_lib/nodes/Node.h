//
// Created by admin on 19.03.2021.
//

#ifndef SDIZO_1_NODE_H
#define SDIZO_1_NODE_H

#include <memory>
#include <string>
#include "../node_util/Side.h"
#include "../Tree.h"

template <typename T>
class Node;

template <typename T>
using NodePointer = std::shared_ptr<Node<T>>;

template <typename T>
using NodeWeakPtr = std::weak_ptr<Node<T>>;

template <typename T>
class Node
{
public:
    virtual T getKey() = 0;
    virtual void setParent(NodePointer<T>) = 0;
    virtual NodePointer<T> getParent() = 0;
    virtual void setLeft(NodePointer<T>) = 0;
    virtual NodePointer<T> getLeft() = 0;
    virtual void setRight(NodePointer<T>) = 0;
    virtual NodePointer<T> getRight() = 0;
    virtual bool isNil() = 0;
    virtual std::string toString() = 0;
    NodePointer<T> get(Side side);
    void setSide(NodePointer<T> node, Side side);
    virtual void copy(Tree<T>& output);
    virtual bool isContainedIn(const Tree<T>& tree);
};

template<typename T>
NodePointer<T> Node<T>::get(Side side) {
    if(side == Side::RIGHT)
        return getRight();
    else
        return getLeft();
}

template<typename T>
void Node<T>::setSide(NodePointer<T> node, Side side) {
    if(side == Side::RIGHT)
        return setRight(node);
    else
        return setLeft(node);
}

template<typename T>
void Node<T>::copy(Tree <T> &output) {
    this->getLeft()->copy(output);
    this->getRight()->copy(output);
    output.put(this->getKey());
}

template<typename T>
bool Node<T>::isContainedIn(const Tree<T> &tree) {
    return tree.contains(getKey()) && getRight()->isContainedIn(tree)
                && getLeft()->isContainedIn(tree);
}

#endif //SDIZO_1_NODE_H
