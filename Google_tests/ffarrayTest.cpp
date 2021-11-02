#include "gtest/gtest.h"

#include "../structure_templates_lib/array_lib/ffarray.h"

TEST(ffarraySuite, firstTest){
    auto array = ffarray<int>(5);
    ASSERT_EQ(5, array.getLength());
}

TEST(ffarraySuite, writeReadTest){
    auto array = ffarray<int>(5);
    array[3] = 5;
    array[1] = 0;
    ASSERT_EQ(5, array[3]);
    ASSERT_EQ(0, array[1]);
}

TEST(ffarraySuite, nestedTest){
    auto array = ffarray<ffarray<int>>(1);
    //array[3] = ffarray<int>(1);
    //array[3][0] = 777;
    //ASSERT_EQ(777, array[3][0]);
}