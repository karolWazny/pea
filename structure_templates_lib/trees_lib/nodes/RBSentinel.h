#ifndef SDIZO_1_RBSENTINEL_H
#define SDIZO_1_RBSENTINEL_H

#include "RBNode.h"
#include "Sentinel.h"
#include "colors/Black.h"
#include "../Tree.h"

template <typename T>
class RBSentinel : public RBNode<T>
{
public:
    RBSentinel();
    explicit RBSentinel(NodePointer<T>& node);

    T getKey() const override;
    virtual void setParent(NodePointer<T>);
    virtual NodePointer<T> getParent() const override;
    virtual void setLeft(NodePointer<T>);
    virtual NodePointer<T> getLeft() const override;
    virtual void setRight(NodePointer<T>);
    virtual NodePointer<T> getRight() const override;
    virtual bool isNil() const override;
    [[nodiscard]] std::string toString() const override;
    void copy(Tree<T>& output) const override;
    bool isContainedIn(const Tree<T>& tree) const override;
    void inOrderList(LinkedList<T>& list) const override;

    virtual bool isBlack() const override;
    virtual bool isRed() const override;
    virtual void paintBlack();
    virtual void paintRed();
#if DEBUG
    int checkAmountOfBlackToLeaves() override;
#endif
    static RBNodePtr<T> getInstance();

private:
    static T key;
    Black black;

    NodePointer<T>& parent;

    NodePointer<T> parentPointer;

    static NodePointer<T> instance;
};

template <typename T>
NodePointer<T> RBSentinel<T>::instance = RBNodePtr<T>(new RBSentinel<T>());

template <typename T>
T RBSentinel<T>::key = NULL;

template<typename T>
RBSentinel<T>::RBSentinel(NodePointer<T>& node):parent(parentPointer) {
    this->black = Black();
    parent = node;
}

template<typename T>
RBSentinel<T>::RBSentinel():parent(instance) {
    this->black = Black();
}

template<typename T>
T RBSentinel<T>::getKey() const {
    return key;
}

template<typename T>
void RBSentinel<T>::setParent(NodePointer<T> node) {
    if(parent != instance)
        parent = node;
}

template<typename T>
NodePointer<T> RBSentinel<T>::getParent() const {
    return parent;
}

template<typename T>
void RBSentinel<T>::setLeft(NodePointer<T>) {

}

template<typename T>
NodePointer<T> RBSentinel<T>::getLeft() const {
    return getInstance();
}

template<typename T>
void RBSentinel<T>::setRight(NodePointer<T>) {

}

template<typename T>
NodePointer<T> RBSentinel<T>::getRight() const {
    return getInstance();
}

template<typename T>
bool RBSentinel<T>::isNil() const {
    return true;
}

template<typename T>
RBNodePtr<T> RBSentinel<T>::getInstance() {
    return rbcast(instance);
}

template<typename T>
bool RBSentinel<T>::isBlack() const {
    return black.isBlack();
}

template<typename T>
bool RBSentinel<T>::isRed() const {
    return black.isRed();
}

template<typename T>
void RBSentinel<T>::paintBlack() {
    black.paintBlack();
}

template<typename T>
void RBSentinel<T>::paintRed() {
    black.paintRed();
}

#if DEBUG
template<typename T>
int RBSentinel<T>::checkAmountOfBlackToLeaves() {
    return 1;
}
#endif

template<typename T>
std::string RBSentinel<T>::toString() const {
    return "B-NIL";
}

template<typename T>
void RBSentinel<T>::copy(Tree <T> &output) const {
    //do nothing
}

template<typename T>
bool RBSentinel<T>::isContainedIn(const Tree<T> &tree) const {
    return true;
}

template<typename T>
void RBSentinel<T>::inOrderList(LinkedList<T> &list) const {
    //do nothing
}

#endif //SDIZO_1_RBSENTINEL_H
