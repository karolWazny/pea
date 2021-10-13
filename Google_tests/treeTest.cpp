#include "gtest/gtest.h"
#include "../structure_templates_lib/trees_lib/RedBlackTree.h"
#include <iostream>

TEST(RedBlackTestSuite, Compilation){
    auto tree = RedBlackTree<int>();
}

TEST(RedBlackTestSuite, PutContains){
    auto tree = RedBlackTree<int>();
    ASSERT_FALSE(tree.contains(4));
    tree.put(4);
    ASSERT_TRUE(tree.contains(4));
    ASSERT_FALSE(tree.contains(5));
    tree.put(5);
    ASSERT_TRUE(tree.contains(5));
    ASSERT_TRUE(tree.contains(4));
}

TEST(RedBlackTestSuite, RemoveRoot){
    auto tree = RedBlackTree<int>();
    tree.put(23);
    tree.put(50);
    tree.put(10);
    tree.put(60);
    tree.put(40);
    ASSERT_TRUE(tree.contains(23));
    ASSERT_TRUE(tree.contains(50));
    ASSERT_TRUE(tree.contains(10));
    ASSERT_TRUE(tree.contains(60));
    ASSERT_TRUE(tree.contains(40));
    tree.remove(23);
    ASSERT_FALSE(tree.contains(23));
    ASSERT_TRUE(tree.contains(50));
    ASSERT_TRUE(tree.contains(10));
    ASSERT_TRUE(tree.contains(60));
    ASSERT_TRUE(tree.contains(40));
}


TEST(RedBlackTestSuite, DeletingSmallest){
    auto tree = RedBlackTree<int>();
    for(int i = 0; i < 100; i++)
    {
        tree.put(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.contains(i));
        if(i == 2)
            tree.remove(i);
        else
            tree.remove(i);
        for(int j = 0; j <= i; j++)
        {
            if(j == 99)
                ASSERT_FALSE(tree.contains(99));
            else
                ASSERT_FALSE(tree.contains(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}

TEST(RedBlackTestSuite, DeletingSmallestSmallAmount){
    auto tree = RedBlackTree<int>();
    for(int i = 0; i < 10; i++)
    {
        tree.put(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
    for(int i = 0; i < 10; i++)
    {
        //std::cout<<tree.toString()<<std::endl;
        ASSERT_TRUE(tree.contains(i));
        tree.remove(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_FALSE(tree.contains(j));
        }
        for(int j = i + 1; j < 10; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}

TEST(RedBlackTestSuite, DeletingReversedAdding){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        if(i == 94)
            tree.put(i);
        else
            tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.contains(i));
        tree.remove(i);
        for(int j = 0; j <= i; j++)
        {
            if(j == 99)
                ASSERT_FALSE(tree.contains(99));
            else
                ASSERT_FALSE(tree.contains(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}
TEST(RedBlackTestSuite, DeletingGreatest){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
    for(int i = 99; i >= 0; i--)
    {
        ASSERT_TRUE(tree.contains(i));
        tree.remove(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_FALSE(tree.contains(j));
        }
        for(int j = i -1; j >=0; j--)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}

TEST(RedBlackTestSuite, AddingGreatestDeletingSmallest){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        tree.put(i);
        for(int j = 99; j >= i; j--)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.contains(i));
        tree.remove(i);
        for(int j = 0; j <= i; j++)
        {
            ASSERT_FALSE(tree.contains(j));
        }
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}

TEST(RedBlackTestSuite, NonUniqueKeys){
    auto tree = RedBlackTree<int>();
    for(int i = 99; i >= 0; i--)
    {
        for(int k = 0; k < 5; k++)
        {
            if(i == 98 && k == 1)
            {
                tree.put(i);
            }
            else
                tree.put(i);
        }
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.contains(i));
        if(i == 0)
        {
            tree.remove(i);
        }
        else
            tree.remove(i);
        ASSERT_TRUE(tree.contains(i));
    }
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(tree.contains(i));
        tree.remove(i);
        for(int j = i + 1; j < 100; j++)
        {
            ASSERT_TRUE(tree.contains(j));
        }
    }
}

TEST(RedBlackTestSuite, NonUniqueKeysSmall){
    auto tree = RedBlackTree<int>();
    tree.put(5);
    tree.put(5);
    tree.put(7);
    tree.put(7);
    tree.put(6);
    tree.put(4);
    tree.put(4);
}

TEST(RedBlackTestSuite, CopyEquals){
    auto tree = RedBlackTree<int>();
    tree.put(5);
    tree.put(7);
    tree.put(6);
    tree.put(4);

    auto secondTree = RedBlackTree<int>();
    ASSERT_FALSE(secondTree==tree);
    auto copy = tree.copy();
    ASSERT_TRUE(tree == copy);
    copy.put(9);
    ASSERT_FALSE(tree==copy);
    ASSERT_TRUE(tree!=copy);
}