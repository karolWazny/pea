#ifndef SDIZO_1_COLORED_H
#define SDIZO_1_COLORED_H

class Colored
{
public:
    [[nodiscard]] virtual bool isBlack() const = 0;
    [[nodiscard]] virtual bool isRed() const = 0;
    virtual void paintBlack() = 0;
    virtual void paintRed() = 0;
};

#endif //SDIZO_1_COLORED_H
