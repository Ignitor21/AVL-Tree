#pragma once

#include <iostream>
#include <algorithm>

namespace avl
{
struct AVLNode
{
    int key;
    int height;
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(0), parent(nullptr), left(nullptr), right(nullptr) {}
};

void print_subtree(AVLNode* top)
{
    if (top != nullptr) 
    { 
        print_subtree(top->left);
        std::cout << top->key << " "; 
        print_subtree(top->right);
    }
}

int balance_factor(AVLNode* node)
{
    if (node == nullptr)
        return -1;
    int left_height = (node->left == nullptr) ? 0 : node->left->height;
    int right_height = (node->right == nullptr) ? 0 : node->right->height;

    return left_height - right_height;
}

int get_height(AVLNode* node)
{
    if (node == nullptr)
        return -1;
    
    return node->height;
}

struct AVLTree
{
    AVLNode* root;
    int size;

    AVLTree(int k) : root(new AVLNode(k)), size(1) {}
    AVLTree() : root(nullptr), size(0) {}

    AVLNode* insert(int k)
    {
        AVLNode* cur{root};
        AVLNode* prev{};

        while(cur != nullptr)
        {
            prev = cur;
            if (k < cur->key)
                cur = cur->left;
            else if (k > cur->key)
                cur = cur->right;
            else
                return cur;
        }

        size++;
        cur = new AVLNode(k);

        if(prev == nullptr)
        {
            root = cur;
            return cur;
        }

        if (k > prev->key)
        {
            prev->right = cur;
        }
        else
        {
            prev->left = cur;
        }

        cur->parent = prev;
        prev->height = std::max(get_height(prev->left), get_height(prev->right)) + 1;
        
        return cur;
    }

};

}