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

    AVLNode(int k) : key(k), height(1), parent(nullptr), left(nullptr), right(nullptr) {}
};

int balance_factor(AVLNode* node)
{
    if (!node)
        return 0;
    int left_height = (node->left == nullptr) ? 0 : node->left->height;
    int right_height = (node->right == nullptr) ? 0 : node->right->height;

    return left_height - right_height;
}

int get_height(AVLNode* node)
{
    if (!node)
        return 0; 
    
    return node->height;
}

void fix_height(AVLNode* node)
{
    if (!node)
        return;

    int hl = get_height(node->right);
    int hr = get_height(node->left);
    node->height = std::max(hl, hr) + 1;
}

class AVLTree
{
    AVLNode* root;
    int size;
public:
    AVLTree(int k) : root(new AVLNode(k)), size(1) {}
    AVLTree() : root(nullptr), size(0) {}

    ~AVLTree()
    {
        FreeAVLTree(root);
    }

private:
    void FreeAVLTree(AVLNode* node)
    {
        if(node)
        {
            FreeAVLTree(node->left);
            FreeAVLTree(node->right);
            delete node;
        }
    }

    void recursive_print(AVLNode* node)
    {
        if (node) 
        { 
            recursive_print(node->left);
            std::cout << node->key << '(' << balance_factor(node) << ") "; 
            recursive_print(node->right); 
        }
    }

    AVLNode* rotate_right(AVLNode* a)
    {
        AVLNode* b = a->left;
        a->left = b->right;
        b->right = a;
        b->parent = a->parent;
        a->parent = b;

        if (!b->parent)
            root = b;

        if (a->left)
            a->left->parent = a;

        fix_height(a);
        fix_height(b);
        return b;
    }

    AVLNode* rotate_left(AVLNode* a) 
    {
        AVLNode* b = a->right;
        a->right = b->left;
        b->left = a;
        b->parent = a->parent;
        a->parent = b;

        if (!b->parent)
            root = b;

        if (a->left)
            a->left->parent = a;

        fix_height(a);
        fix_height(b);
        return b; 
    }

    AVLNode* balance(AVLNode* p) 
    {
        int bf = balance_factor(p);
        if(bf == 2)
        {
            p = rotate_right(p);
        }
        if(bf == -2)
        {
            p = rotate_left(p);
        }
        return p; 
    }

public:
    void tree_dump()
    {
        recursive_print(root);
        std::cout << "\n";
    }

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

        while(prev)
        {
            fix_height(prev);
            prev = balance(prev);
            prev = prev->parent;
        }

        return cur;
    }

};

}