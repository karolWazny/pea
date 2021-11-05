#include "node.h"


rbnode::rbnode(){

}

rbnode::~rbnode(){

}

//GETTERY
rbnode* rbnode::getParent(){
    return this->parent;
}

rbnode* rbnode::getLeft(){
    return this->left;
}

rbnode* rbnode::getRight(){
    return this->right;
}

int rbnode::getKey(){
    return this->key;
}

char rbnode::getColor(){
    return this->color;
}

//SETTERY
void rbnode::setParent(rbnode* Parent){
    this->parent = Parent;
}

void rbnode::setLeft(rbnode* leftSon){
    this->left = leftSon;
}

void rbnode::setRight(rbnode* rightSon){
    this->right = rightSon;
}

void rbnode::setKey(int Key){
    this->key = Key;
}

void rbnode::setColor(char Color){
    this->color = Color;
}