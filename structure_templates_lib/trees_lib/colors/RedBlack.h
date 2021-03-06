#ifndef SDIZO_1_REDBLACK_H
#define SDIZO_1_REDBLACK_H

#include "Colored.h"

enum class Color : char
{
    RED,
    BLACK
};

class RedBlack : public Colored
{
public:
    [[nodiscard]] bool isBlack() const override;
    [[nodiscard]] bool isRed() const override;
    void paintBlack() override;
    void paintRed() override;
private:
    Color color;
};

#endif //SDIZO_1_REDBLACK_H
