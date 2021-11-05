#pragma once

#include "node.h"
class BRTree
{
private:

    rbnode* NIL{};
    rbnode* root{};
    int size{};

    void copyRecursively(BRTree& tree, rbnode* node);
    void recursiveDestructor(rbnode* node);

public:
    BRTree();
    ~BRTree();

    bool contains(int key);
    void copyTo(BRTree& copy);

    //BRTree& operator=(BRTree&& tree) noexcept;

    void inorderTreeWalk(rbnode* node);
    rbnode* treeSearch(rbnode* node, int k);
    rbnode* treeMinimum(rbnode* node);
    rbnode* treeMaximum(rbnode* node);
    rbnode* treeSuccessor(rbnode* node);
    rbnode* treePredecessor(rbnode* node);
    void treeInsert(rbnode* input);
    void treeDelete(rbnode* out);
    void leftRotate(rbnode* node);
    void rightRotate(rbnode* node);
    void put(int value);
    void deleteElement(int value);

    //GETTERY
    rbnode* getRoot();
    [[nodiscard]] int getSize() const;
    rbnode* getNIL();
    //SETTERY
    void setRoot(rbnode* Root);
};
