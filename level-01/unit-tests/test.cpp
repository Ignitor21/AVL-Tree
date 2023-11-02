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
    EXPECT_EQ(tree.end(), tree.find_by_number(15));
    EXPECT_EQ(tree.end(), tree.find_by_number(-777));
    EXPECT_EQ(tree.end(), tree.find_by_number(0));
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

TEST(ITERATORS, traverse)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    std::vector<int> expected_ans {2, 7, 10, 14, 20, 27, 30, 50};
    std::vector<int> ans;

    for (auto it = tree.begin(), end = tree.end(); it != end; ++it)
        ans.push_back(*it);

    EXPECT_EQ(ans, expected_ans);
}

TEST(BIG_FIVE, copy_constructor)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    AVLTree<int> new_tree {tree};

    std::vector<int> expected_ans {2, 7, 10, 14, 20, 27, 30, 50};
    std::vector<int> ans;

    for (auto it = new_tree.begin(), end = new_tree.end(); it != end; ++it)
        ans.push_back(*it);
    
    EXPECT_EQ(expected_ans, ans);
}

TEST(BIG_FIVE, move_constructor)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }


    std::vector<int> expected_ans;

    for (auto it = tree.begin(), end = tree.end(); it != end; ++it)
        expected_ans.push_back(*it);

    AVLTree<int> new_tree = std::move(tree);
    std::vector<int> ans;

    for (auto it = new_tree.begin(), end = new_tree.end(); it != end; ++it)
        ans.push_back(*it);
    
    EXPECT_EQ(expected_ans, ans);
}

TEST(BIG_FIVE, copy_assignment)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    AVLTree<int> new_tree;
    new_tree = tree;

    std::vector<int> expected_ans;
    std::vector<int> ans;

    for (auto it = tree.begin(), end = tree.end(); it != end; ++it)
        expected_ans.push_back(*it);

    for (auto it = new_tree.begin(), end = new_tree.end(); it != end; ++it)
        ans.push_back(*it);
    
    EXPECT_EQ(expected_ans, ans);
}

TEST(BIG_FIVE, move_assignment)
{
    AVLTree<int> tree{};
    std::vector<int> input{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input)
    {
        tree.insert(x);
    }

    std::vector<int> expected_ans;
    for (auto it = tree.begin(), end = tree.end(); it != end; ++it)
        expected_ans.push_back(*it);

    AVLTree<int> new_tree;
    new_tree = std::move(tree);

    std::vector<int> ans;
    for (auto it = new_tree.begin(), end = new_tree.end(); it != end; ++it)
        ans.push_back(*it);
    
    EXPECT_EQ(expected_ans, ans);
}

int main(int argc, char** argv)
{   
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}