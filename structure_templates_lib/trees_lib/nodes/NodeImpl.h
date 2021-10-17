#ifndef SDIZO_1_NODEIMPL_H
#define SDIZO_1_NODEIMPL_H

#include "Node.h"
#include "Sentinel.h"

template <typename T>
class NodeImpl : public Node<T>
{
public:
    explicit NodeImpl(T key);
    T getKey() const override;
    void setParent(NodePointer<T>) override;
    NodePointer<T> getParent() const override;
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() const override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() const override;
    [[nodiscard]] bool isNil() const override;
    [[nodiscard]] std::string toString() const override;
private:
    T key;
    NodePointer<T> right;
    NodePointer<T> left;
    NodeWeakPtr<T> parent;
    static NodePointer<T> sentinel;
};

template <typename T>
NodePointer<T> NodeImpl<T>::sentinel = Sentinel<T>::getInstance();


template<typename T>
NodeImpl<T>::NodeImpl(T key) {
    this->key = key;
    right = sentinel;
    left = sentinel;
    parent = sentinel;
}

template<typename T>
T NodeImpl<T>::getKey() const {
    return key;
}

template<typename T>
NodePointer<T> NodeImpl<T>::getParent() const{
    return parent.lock();
}

template<typename T>
NodePointer<T> NodeImpl<T>::getLeft() const {
    return left;
}

template<typename T>
NodePointer<T> NodeImpl<T>::getRight() const {
    return right;
}

template<typename T>
bool NodeImpl<T>::isNil() const {
    return false;
}

template<typename T>
void NodeImpl<T>::setLeft(NodePointer<T> node) {
    if(node)
        this->left = node;
    else
        this->left = sentinel;
}

template<typename T>
void NodeImpl<T>::setRight(NodePointer<T> node) {
    if(node)
        this->right = node;
    else
        this->right = sentinel;
}

template<typename T>
void NodeImpl<T>::setParent(NodePointer<T> node) {
    if(node)
        this->parent = node;
    else
        this->parent = sentinel;
}

template<typename T>
std::string NodeImpl<T>::toString() const {
    return std::to_string(getKey());
}

#endif //SDIZO_1_NODEIMPL_H
