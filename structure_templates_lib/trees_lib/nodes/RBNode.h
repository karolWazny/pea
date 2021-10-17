#ifndef SDIZO_1_RBNODE_H
#define SDIZO_1_RBNODE_H

#include "colors/Colored.h"
#include "Node.h"

template <typename T>
class RBNode;

template <typename T>
using RBNodePtr = std::shared_ptr<RBNode<T>>;

template <typename T>
class RBNode : public Colored, public Node<T>
{
public:
    virtual T getKey() const = 0;
    virtual void setParent(NodePointer<T>) = 0;
    virtual NodePointer<T> getParent() const = 0;
    virtual void setLeft(NodePointer<T>) = 0;
    virtual NodePointer<T> getLeft() const = 0;
    virtual void setRight(NodePointer<T>) = 0;
    virtual NodePointer<T> getRight() const = 0;
#if DEBUG
    virtual int checkAmountOfBlackToLeaves() = 0;
#endif
};

template <typename T>
RBNodePtr<T> rbcast(NodePointer<T> node) {
    return std::dynamic_pointer_cast<RBNode<T>>(node);
}

#endif //SDIZO_1_RBNODE_H
