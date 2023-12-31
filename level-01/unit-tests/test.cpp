#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <gtest/gtest.h>
#include "avl.hpp"

using namespace avl;

TEST(AVL_FUNCTIONS, insert)
{
    AVLTree<int> tree{};
    auto n1 = tree.insert(1337);
    auto n2 = tree.insert(228);
    auto n3 = tree.insert(-1);
    auto n4 = tree.insert(21);

    EXPECT_EQ(*n1, 1337);
    EXPECT_EQ(*n2, 228);
    EXPECT_EQ(*n3, -1);
    EXPECT_EQ(*n4, 21); 
}

TEST(AVL_FUNCTIONS, find)
{
    AVLTree<int> tree{};
    auto n1 = tree.insert(1337);
    auto n2 = tree.insert(228);
    auto n3 = tree.insert(-1);
    tree.insert(21);
    tree.insert(1487);

    EXPECT_EQ(n1, tree.find(1337));
    EXPECT_EQ(n2, tree.find(228));
    EXPECT_EQ(tree.end(), tree.find(1488));
    EXPECT_EQ(n3, tree.find(-1));
}

TEST(AVL_FUNCTIONS, distance)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    EXPECT_EQ(0, tree.distance(51, 60));
    EXPECT_EQ(0, tree.distance(-5, 0));
    EXPECT_EQ(0, tree.distance(1337, 228));
    EXPECT_EQ(6, tree.distance(10, 50));
    EXPECT_EQ(5, tree.distance(3, 27));
    EXPECT_EQ(4, tree.distance(14, 34));
    EXPECT_EQ(2, tree.distance(19, 28));
}

int main(int argc, char** argv)
{   
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}