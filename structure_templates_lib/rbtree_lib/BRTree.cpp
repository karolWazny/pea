#include "BRTree.h"


BRTree::BRTree(){
    this->NIL = new rbnode();
    this->NIL->setColor('B');
    this->NIL->setParent(this->NIL);
    this->NIL->setLeft(this->NIL);
    this->NIL->setRight(this->NIL);
    this->root = this->NIL;
}

BRTree::~BRTree(){
    recursiveDestructor(root);
    delete NIL;
}

//Operacje jak dla normalnego drzewa BST
void BRTree::inorderTreeWalk(rbnode* node){
    if(node != this->NIL){
        inorderTreeWalk(node->getLeft());
        std::cout << " " << node->getColor() << node->getKey() << " ";
        inorderTreeWalk(node->getRight());
    }
}

rbnode* BRTree::treeSearch(rbnode* node, int k){
    if(node == this->NIL || k == node->getKey()){
        return node;
    }

    if(k <= node->getKey()){
        return treeSearch(node->getLeft(), k);
    }
    else{
        return treeSearch(node->getRight(), k);
    }
}

rbnode* BRTree::treeMinimum(rbnode* node){
    while(node->getLeft() != this->NIL){
        node = node->getLeft();
    }
    return node;
}

rbnode* BRTree::treeMaximum(rbnode* node){
    while(node->getRight() != this->NIL){
        node = node->getRight();
    }
    return node;
}

rbnode* BRTree::treeSuccessor(rbnode* node){
    if(node->getRight() != this->NIL){
        return treeMinimum(node->getRight());
    }
    rbnode* y = node->getParent();
    while(y!=this->NIL && node == y->getRight()){
        node = y;
        y = y->getParent();
    }
    return y;
}

rbnode* BRTree::treePredecessor(rbnode* node){
    rbnode* y;
    if(node->getLeft() != this->NIL){
        return treeMaximum(node);
    }
    y = node->getParent();
    while(y != this->NIL && node == y->getLeft()){
        node = y;
        y = y->getParent();
    }
    return y;
}

void BRTree::treeInsert(rbnode* input){
    rbnode* y = this->NIL;
    rbnode* x = this->getRoot();

    while(x != this->NIL){
        y = x;
        if(input->getKey() < x->getKey()){
            x = x->getLeft();
        }
        else{
            x = x->getRight();
        }
    }

    input->setParent(y);

    if(y == this->NIL){
        this->setRoot(input);
    }
    else{
        if(input->getKey() < y->getKey()){
            y->setLeft(input);
        }
        else{
            y->setRight(input);
        }
    }
}

void BRTree::treeDelete(rbnode* out){
    rbnode* y = this->NIL;
    rbnode* x;

    if(out->getLeft() == this->NIL || out->getRight() == this->NIL){
        y = out;
    }
    else{
        y = treeSuccessor(out);
    }

    if(y->getLeft() != this->NIL){
        x = y->getLeft();
    }
    else{
        x = y->getRight();
    }

    if(x != this->NIL){
        x->setParent(y->getParent());
    }

    //Od tego momentu Cormen inny algorytm wskazuje
    if(y->getParent() != this->NIL){
        this->setRoot(x);
    }
    else{
        if(y == y->getParent()->getLeft()){
            y->getParent()->setLeft(x);
        }
        /*else{
            y->getParent()->setRight(x);
        }*/
    }

    /*if(y!=out){
        out->setKey(y->getKey());
    }
    return y;*/
}

void BRTree::leftRotate(rbnode* node){
    rbnode* x;
    rbnode* y;

    y = node->getRight();
    if(y != this->NIL){
        x = node->getParent();
        node->setRight(y->getLeft());

        if(node->getRight() != this->NIL){
            node->getRight()->setParent(node);
        }

        y->setLeft(node);
        y->setParent(x);
        node->setParent(y);

        if(x != this->NIL){
            if(x->getLeft() == node){
                x->setLeft(y);
            }
            else{
                x->setRight(y);
            }
        }
        else{
            this->setRoot(y);
        }
    }
}

void BRTree::rightRotate(rbnode* node){
    rbnode* x;
    rbnode* y;

    y = node->getLeft();
    if(y != this->NIL){
        x = node->getParent();
        node->setLeft(y->getRight());

        if(node->getLeft() != this->NIL){
            node->getLeft()->setParent(node);
        }

        y->setRight(node);
        y->setParent(x);
        node->setParent(y);

        if(x != this->NIL){
            if(x->getLeft() == node){
                x->setLeft(y);
            }
            else{
                x->setRight(y);
            }
        }
        else{
            this->setRoot(y);
        }
    }
}

//Nie mam pojęcia czy to zadziała
void BRTree::put(int value){
    rbnode* x;
    rbnode* y;

    x = new rbnode();
    x->setLeft(this->NIL);
    x->setRight(this->NIL);
    x->setParent(this->getRoot());
    //x->setColor('B');
    x->setKey(value);

    if(x->getParent() == this->NIL){
        this->setRoot(x);
        this->getRoot()->setColor('B');
        this->size++;
    }
    else{
        while(true){
            //Zmienić na <= jesli mogą się powtarzać wartości kluczy
            if(value <= x->getParent()->getKey()){
                if(x->getParent()->getLeft() == this->NIL){
                    x->getParent()->setLeft(x);
                    break;
                }

                x->setParent(x->getParent()->getLeft());
            }
            else if(value > x->getParent()->getKey()){
                if(x->getParent()->getRight() == this->NIL){
                    x->getParent()->setRight(x);
                    break;
                }

                x->setParent(x->getParent()->getRight());
            }
            //Zakomentować blok else, jeśli się mogą powtarzać wartości kluczy
            /*else{
                delete x;
                return;
            }*/
        }

        //Kolorowanie na czerwono
        x->setColor('R');
        while((x != this->root) && (x->getParent()->getColor() == 'R')){
            if(x->getParent() == x->getParent()->getParent()->getLeft()){
                y = x->getParent()->getParent()->getRight();


                //Przypadek 1
                if(y && y->getColor() == 'R'){
                    x->getParent()->setColor('B');
                    y->setColor('B');
                    x->getParent()->getParent()->setColor('R');
                    x = x->getParent()->getParent();
                    continue;
                }

                //Przypadek 2
                if(x == x->getParent()->getRight()){
                    x = x->getParent();
                    leftRotate(x);
                }

                //Przypadek 3
                x->getParent()->setColor('B');
                x->getParent()->getParent()->setColor('R');
                rightRotate(x->getParent()->getParent());
                break;
            }
            else{
                y = x->getParent()->getParent()->getLeft();

                //Przypadek 1
                if(y && y->getColor() == 'R'){
                    x->getParent()->setColor('B');
                    y->setColor('B');
                    x->getParent()->getParent()->setColor('R');
                    x = x->getParent()->getParent();
                    continue;
                }

                //Przypadek 2
                if(x == x->getParent()->getLeft()){
                    x = x->getParent();
                    rightRotate(x);
                }

                //Przypadek 3
                x->getParent()->setColor('B');
                x->getParent()->getParent()->setColor('R');
                leftRotate(x->getParent()->getParent());
                break;
            }
        }
        this->getRoot()->setColor('B');
        this->size++;
    }
}

//Nie mam pojęcia czy to zadziała...
void BRTree::deleteElement(int value){
    rbnode* node;
    rbnode* x;
    rbnode* y;
    rbnode* z;

    node = treeSearch(this->getRoot(), value);

    if((node->getLeft() == this->NIL) || (node->getRight() == this->NIL)){
        y = node;
    }
    else{
        y = treeSuccessor(node);
    }

    if(y->getLeft() != this->NIL){
        z = y->getLeft();
    }
    else{
        z = y->getRight();
    }

    z->setParent(y->getParent());

    if(y->getParent() == this->NIL){
        this->setRoot(z);
    }
    else if(y == y->getParent()->getLeft()){
        y->getParent()->setLeft(z);
    }
    else{
        y->getParent()->setRight(z);
    }

    if(y != node){
        node->setKey(y->getKey());
    }

    //Odbudowa struktury drzewa czerwono-czarnego
    if(y && y->getColor() == 'B'){
        while(z && (z != this->getRoot()) && (z->getColor() == 'B')){
            if(z == z->getParent()->getLeft()){

                x = z->getParent()->getRight();

                //Przypadek 1
                if(x && x->getColor() == 'R'){
                    x->setColor('B');
                    z->getParent()->setColor('R');
                    leftRotate(z->getParent());
                    x = z->getParent()->getRight();
                }

                //Przypadek 2
                if(x && (x->getLeft()->getColor() == 'B') && (x->getRight()->getColor() == 'B')){
                    x->setColor('R');
                    z = z->getParent();
                    continue;
                }

                //Przypadek 3
                if(x && x->getRight()->getColor() == 'B'){
                    x->getLeft()->setColor('B');
                    x->setColor('R');
                    rightRotate(x);
                    x = z->getParent()->getRight();
                }

                //Przypadek 4
                x->setColor(z->getParent()->getColor());
                z->getParent()->setColor('B');
                x->getRight()->setColor('B');
                leftRotate(z->getParent());

                z = this->getRoot();
            }
            else{
                x = z->getParent()->getLeft();

                //Przypadek 1
                if(x && x->getColor() == 'R'){
                    x->setColor('B');
                    z->getParent()->setColor('R');
                    leftRotate(z->getParent());
                    x = z->getParent()->getLeft();
                }

                //Przypadek 2
                if(x && (x->getLeft()->getColor() == 'B') && (x->getRight()->getColor() == 'B')){
                    x->setColor('R');
                    z = z->getParent();
                    continue;
                }

                //Przypadek 3
                if(x && x->getLeft()->getColor() == 'B'){
                    x->getRight()->setColor('B');
                    x->setColor('R');
                    leftRotate(x);
                    x = z->getParent()->getLeft();
                }

                //Przypadek 4
                x->setColor(z->getParent()->getColor());
                z->getParent()->setColor('B');
                x->getLeft()->setColor('B');
                rightRotate(z->getParent());

                z = this->getRoot();
            }
        }
        z->setColor('B');
        delete y;
    }
}

//GETTERY
rbnode* BRTree::getRoot(){
    return this->root;
}

int BRTree::getSize() const{
    return this->size;
}

rbnode* BRTree::getNIL(){
    return this->NIL;
}
//SETTERY
void BRTree::setRoot(rbnode* Root){
    this->root = Root;
}

bool BRTree::contains(int key) {
    return this->treeSearch(this->root, key) != this->NIL;
}

void BRTree::copyTo(BRTree& copy) {
    copy.recursiveDestructor(copy.root);
    copyRecursively(copy, root);
}

void BRTree::copyRecursively(BRTree& tree, rbnode* node){
    if(node == this->NIL)
        return;
    tree.put(node->getKey());
    copyRecursively(tree, node->getLeft());
    copyRecursively(tree, node->getRight());
}

void BRTree::recursiveDestructor(rbnode* node) {
    if(node == NIL)
        return;
    recursiveDestructor(node->getLeft());
    recursiveDestructor(node->getRight());
    delete node;
}

/*BRTree &BRTree::operator=(BRTree&& tree)  noexcept {
    this->recursiveDestructor(root);
    delete NIL;
    this->NIL = tree.NIL;
    this->size = tree.size;
    this->root = tree.root;
    tree.root = nullptr;
    tree.NIL = nullptr;
    return *this;
}*/
