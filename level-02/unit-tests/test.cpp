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

TEST(AVL_FUNCTIONS, find_by_number)
{
    AVLTree<int> tree{};
    std::vector<int> input{21, 28, 32, 15, 13, 88, 36, 8, 9, 1};
    // 1 8 9 13 15 21 28 32 36 88
    for (const auto& x: input)
    {
        tree.insert(x);
    }

    EXPECT_EQ(28, *(tree.find_by_number(7)));
    EXPECT_EQ(88, *(tree.find_by_number(10)));
    EXPECT_EQ(1, *(tree.find_by_number(1)));
    EXPECT_EQ(88, *(tree.find_by_number(15)));
    EXPECT_THROW(tree.find_by_number(-777), std::range_error);
    EXPECT_THROW(tree.find_by_number(0), std::range_error);
}

TEST(AVL_FUNCTIONS, less_than)
{
    AVLTree<int> tree{};
    std::vector<int> input{21, 28, 32, 15, 13, 88, 36, 8, 9, 1};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    EXPECT_EQ(7, tree.less_than(32));
    EXPECT_EQ(8, tree.less_than(33));
    EXPECT_EQ(10, tree.less_than(100));
    EXPECT_EQ(0, tree.less_than(-5));
    EXPECT_EQ(4, tree.less_than(15));
}

int main(int argc, char** argv)
{   
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}