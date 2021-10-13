#ifndef SDIZO_1_SENTINEL_H
#define SDIZO_1_SENTINEL_H

#include "Node.h"

template <typename T>
class Sentinel : public Node<T>
{
public:
    T getKey() const override;
    void setParent(NodePointer<T>);
    NodePointer<T> getParent() const override;
    void setLeft(NodePointer<T>) override;
    NodePointer<T> getLeft() const override;
    void setRight(NodePointer<T>) override;
    NodePointer<T> getRight() const override;
    [[nodiscard]] bool isNil() const override;
    std::string toString() const override;
    bool isContainedIn(const Tree<T>& tree) const override;
    void inOrderList(LinkedList<T>& list) const override;

    static NodePointer<T> getInstance();
private:
    static T key;
    static NodePointer<T> instance;
};

template <typename T>
NodePointer<T> Sentinel<T>::instance = NodePointer<T>(new Sentinel<T>());

template <typename T>
T Sentinel<T>::key = NULL;

template<typename T>
NodePointer<T> Sentinel<T>::getParent() const {
    return getInstance();
}

template<typename T>
NodePointer<T> Sentinel<T>::getLeft() const {
    return getInstance();
}

template<typename T>
NodePointer<T> Sentinel<T>::getRight() const{
    return getInstance();
}

template<typename T>
T Sentinel<T>::getKey() const {
    return key;
}

template<typename T>
bool Sentinel<T>::isNil() const {
    return true;
}

template<typename T>
void Sentinel<T>::setLeft(NodePointer<T>) {
    //nil z definicji jest bezdzietny
}

template<typename T>
void Sentinel<T>::setRight(NodePointer<T>) {
    //nil z definicji jest bezdzietny
}

template<typename T>
void Sentinel<T>::setParent(NodePointer<T> parent) {

}

template<typename T>
NodePointer<T> Sentinel<T>::getInstance() {
    return instance;
}

template<typename T>
std::string Sentinel<T>::toString() const {
    return "NIL";
}

template<typename T>
bool Sentinel<T>::isContainedIn(const Tree<T> &tree) const {
    return true;
}

template<typename T>
void Sentinel<T>::inOrderList(LinkedList<T> &list) const {
    //do nothing
}

#endif //SDIZO_1_SENTINEL_H
