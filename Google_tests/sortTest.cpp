#include "gtest/gtest.h"
#include "../structure_templates_lib/array_lib/ffarray.h"
#include "../utils/mathfunctions.h"

TEST(SortingSuite, InitialTest){
    ffarray<int> array = ffarray<int>(1);
    array[0] = 5;
    math::heapSort(array);
    ASSERT_EQ(array[0], 5);
}

TEST(SortingSuite, TrivialTest1){
    ffarray<int> array = ffarray<int>(2);
    array[0] = 5;
    array[1] = 2;
    math::heapSort(array);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 5);
}

TEST(SortingSuite, TrivialTest2){
    ffarray<int> array = ffarray<int>(2);
    array[0] = 2;
    array[1] = 5;
    math::heapSort(array);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 5);
}

TEST(SortingSuite, MediumSizedTest){
    for(int i = 0; i < 30; i++){
        ffarray<int> array = ffarray<int>(8);
        for(int i = 0; i < array.getLength(); i++){
            array[i] = 100 - i;
        }
        math::fisherYatesShuffle(array);
        math::heapSort(array);
        /*for(int i = 0; i < array.getLength() - 1; i++){
            std::cout << std::to_string(array[i]) << " " << std::to_string(array[i + 1])<< std::endl;
        }*/

        for(int i = 0; i < array.getLength() - 1; i++){
            ASSERT_TRUE(array[i] <= array[i + 1]);
        }
    }
}
