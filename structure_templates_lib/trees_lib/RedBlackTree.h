#ifndef SDIZO_1_REDBLACKTREE_H
#define SDIZO_1_REDBLACKTREE_H

#include "nodes/Node.h"
#include "node_util/KeyFinder.h"
#include "nodes/RBFactory.h"
#include "rbutil/RBPutter.h"
#include "rbutil/RBRemover.h"
#include "node_util/TreePrinter.h"
#include "Tree.h"
#include "../linked_list_lib/LinkedList.h"


template <typename T>
class RedBlackTree : public Tree<T>
{
public:
    RedBlackTree();
    RedBlackTree<T> copy();
    void put(T key) override;
    bool contains(T key) const;
    void remove(T key);
    string toString();
    string getRepresentation();
    bool isEmpty();
    bool contains(const Tree<T>&) const override;
    bool isContainedIn(const Tree<T>&) const override;
    bool operator==(const Tree<T>&) const;
    bool operator!=(const Tree<T>&) const;
    LinkedList<T> inOrderList() const override;
private:
    NodePointer<T> root;
};

template <typename T>
RedBlackTree<T>::RedBlackTree() {
    root = SimpleFactory<T>::makeSentinel();
}

template<typename T>
void RedBlackTree<T>::put(T key) {
    auto putter = RBPutter<T>(root);
    putter.put(key);
    root = putter.obtainRoot();
#if DEBUG
    rbcast(root)->checkAmountOfBlackToLeaves();
#endif
}

template<typename T>
bool RedBlackTree<T>::contains(T key) const {
    auto finder = KeyFinder<T>(root);
    finder.setDesiredKey(key);
    finder.find();
    return finder.nodeFound();
}

template<typename T>
void RedBlackTree<T>::remove(T key) {
    auto remover = RBRemover<T>(root);
    remover.remove(key);
    root = remover.obtainRoot();
#if DEBUG
    rbcast(root)->checkAmountOfBlackToLeaves();
#endif
}

template<typename T>
string RedBlackTree<T>::toString() {
    return TreePrinter<T>().toString(root);
}

template<typename T>
string RedBlackTree<T>::getRepresentation() {
    return TreePrinter<T>().rbMonospaceRepresentation(root);
}

template<typename T>
bool RedBlackTree<T>::isEmpty() {
    return root->isNil();
}

template<typename T>
RedBlackTree<T> RedBlackTree<T>::copy() {
    RedBlackTree<T> output;
    root->copy(output);
    return output;
}

template<typename T>
bool RedBlackTree<T>::operator==(const Tree<T> &tree) const {
    return this->contains(tree) && tree.contains(*this);
}

template<typename T>
bool RedBlackTree<T>::operator!=(const Tree<T> &tree) const {
    return !operator==(tree);
}

template<typename T>
bool RedBlackTree<T>::contains(const Tree<T> & tree) const {
    return tree.isContainedIn(*this);
}

template<typename T>
bool RedBlackTree<T>::isContainedIn(const Tree<T> &tree) const {
    return root->isContainedIn(tree);
}

template<typename T>
LinkedList<T> RedBlackTree<T>::inOrderList() const {
    LinkedList<T> result;

    return result;
}

#endif //SDIZO_1_REDBLACKTREE_H
