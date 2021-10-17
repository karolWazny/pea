#include "gtest/gtest.h"

#include "../tspalgorithms/mathfunctions.h"


TEST(MathSuite, nBelowK){
    auto result = math::newton(4, 5);
    ASSERT_EQ(0, result);
}

TEST(MathSuite, nEqualK){
    auto result = math::newton(5, 5);
    ASSERT_EQ(1, result);
}

TEST(MathSuite, kEqualZero){
    auto result = math::newton(4, 0);
    ASSERT_EQ(1, result);
}

TEST(MathSuite, sample){
    ASSERT_EQ(35, math::newton(7, 4));
    ASSERT_EQ(126, math::newton(9, 5));
}