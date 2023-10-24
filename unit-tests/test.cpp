#include <iostream>
#include <vector>
#include <algorithm>
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

    EXPECT_EQ(n1->height, 1);
    EXPECT_EQ(n2->height, 3);
    EXPECT_EQ(n3->height, 2);
    EXPECT_EQ(n4->height, 1);

    EXPECT_EQ(n1->size, 1);
    EXPECT_EQ(n2->size, 4);
    EXPECT_EQ(n3->size, 2);
    EXPECT_EQ(n4->size, 1); 
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

    int ans1 = 28;
    EXPECT_EQ(ans1, tree.find_by_number(7)->key);
    int ans2 = 88;
    EXPECT_EQ(ans2, tree.find_by_number(10)->key);
    int ans3 = 1;
    EXPECT_EQ(ans3, tree.find_by_number(1)->key);
    auto ans4 = nullptr;
    EXPECT_EQ(ans4, tree.find_by_number(15));
    auto ans5 = nullptr;
    EXPECT_EQ(ans5, tree.find_by_number(-777));
    auto ans6 = nullptr;
    EXPECT_EQ(ans6, tree.find_by_number(0));
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
    EXPECT_EQ(nullptr, tree.find(1488));
    EXPECT_EQ(n3, tree.find(-1));
}

TEST(AVL_FUNCTIONS, less_than)
{
    AVLTree<int> tree{};
    std::vector<int> input{21, 28, 32, 15, 13, 88, 36, 8, 9, 1};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    int ans1 = 7;
    EXPECT_EQ(ans1, tree.less_than(32));
    int ans2 = 8;
    EXPECT_EQ(ans2, tree.less_than(33));
    int ans3 = 10;
    EXPECT_EQ(ans3, tree.less_than(100));
    int ans4 = 0;
    EXPECT_EQ(ans4, tree.less_than(-5));
    int ans5 = 4;
    EXPECT_EQ(ans5, tree.less_than(15));
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
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}