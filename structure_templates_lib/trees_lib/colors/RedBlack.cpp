#include "RedBlack.h"

bool RedBlack::isBlack() const {
    return color == Color::BLACK;
}

bool RedBlack::isRed() const {
    return color == Color::RED;
}

void RedBlack::paintBlack() {
    color = Color::BLACK;
}

void RedBlack::paintRed() {
    color = Color::RED;
}