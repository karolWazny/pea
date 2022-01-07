#ifndef PEA_PLANARVECTOR_H
#define PEA_PLANARVECTOR_H


#include <cmath>

class PlanarVector {
private:
    int x{};
    int y{};
public:
    PlanarVector() = default;
    PlanarVector(int x, int y) : x(x), y(y){};
    PlanarVector(PlanarVector const &p) = default;

    friend PlanarVector operator-(PlanarVector lhs, const PlanarVector& rhs){
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    };

    friend PlanarVector operator+(PlanarVector lhs, const PlanarVector& rhs){
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    };

    double getModulus(){
        return std::sqrt(x * x + y * y);
    };

    int getXInt(){
        return x;
    };
    int getYInt(){
        return y;
    };
    double getXD(){
        return x;
    };
    double getYD(){
        return y;
    }

    void setX(int x) {
        PlanarVector::x = x;
    }

    void setY(int y) {
        PlanarVector::y = y;
    }
};


#endif //PEA_PLANARVECTOR_H
