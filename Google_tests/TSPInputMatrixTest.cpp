#include "gtest/gtest.h"
#include "../tspalgorithms/TSPInputMatrix.h"

TEST(TSPMatrixSuite, BuilderTest){
    auto builder = TSPInputMatrix::builder(5);
    builder.setDistance(0, 3, 40);
    builder.setDistance(3, 0, 50);
    builder.setDistance(2, 4, 100);
}

TEST(TSPMatrixSuite, DistanceTest){
    auto builder = TSPInputMatrix::builder(5);
    builder.setDistance(0, 3, 40);
    builder.setDistance(3, 0, 50);
    builder.setDistance(2, 4, 100);
    auto matrix = builder.build();
    ASSERT_EQ(40, matrix.getDistance(0, 3));
    ASSERT_EQ(50, matrix.getDistance(3, 0));
    ASSERT_EQ(100, matrix.getDistance(2, 4));
    ASSERT_EQ(INT32_MAX, matrix.getDistance(4, 2));
}

TEST(TSPMatrixSuite, DistanceToSelfIsZeroTest){
    auto builder = TSPInputMatrix::builder(5);
    builder.setDistance(0, 3, 40);
    builder.setDistance(3, 0, 50);
    auto matrix = builder.build();
    ASSERT_EQ(0, matrix.getDistance(0, 0));
    ASSERT_EQ(0, matrix.getDistance(3, 3));
}