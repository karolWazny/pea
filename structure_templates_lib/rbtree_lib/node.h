#pragma once

#include <iostream>

class rbnode
{
private:
    rbnode* parent;
    rbnode* left;
    rbnode* right;
    int key;
    char color;

public:
    rbnode();
    ~rbnode();

    //GETTERY
    rbnode* getParent();
    rbnode* getLeft();
    rbnode* getRight();
    int getKey();
    char getColor();

    //SETTERY
    void setParent(rbnode* Parent);
    void setLeft(rbnode* leftSon);
    void setRight(rbnode* rightSon);
    void setKey(int Key);
    void setColor(char Color);
};
