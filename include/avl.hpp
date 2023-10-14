#pragma once

#include <iostream>
#include <algorithm>

/* TO-DO:
- big five
- end-to-end tests
- unit test
- graphviz
- comments
*/

namespace avl
{
struct AVLNode
{
    int key;
    int height; // height of max subtree + 1
    int size; // number of nodes in left subtree + right subtree + 1
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(1), size(1), parent(nullptr), left(nullptr), right(nullptr) {}
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

int get_size(AVLNode* node)
{
    if (!node)
        return 0; 
    
    return node->size;
}

void fix_size(AVLNode* node)
{
    if (!node)
        return;
    
    int sl = get_size(node->right);
    int sr = get_size(node->left);

    node->size = sl + sr + 1;
}

class AVLTree
{
    AVLNode* root;
public:
    AVLTree() : root(nullptr) {}

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

    void recursive_print(AVLNode* node) const
    {
        if (node) 
        { 
            recursive_print(node->left);
            std::cout << node->key << '(' << balance_factor(node) << ", " << get_size(node) << ") "; 
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
        else
        {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }

        if (a->left)
            a->left->parent = a;

        fix_height(a);
        fix_height(b);
        fix_size(a);
        fix_size(b);
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
        else
        {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }

        if (a->left)
            a->left->parent = a;

        fix_height(a);
        fix_height(b);
        fix_size(a);
        fix_size(b);
        return b; 
    }

    AVLNode* balance(AVLNode* p) 
    {
        int bf = balance_factor(p);
        if(bf == 2)
        {
            if (get_height(p->left->right) > get_height(p->left->left))
                p->left = rotate_left(p->left); //big left rotation
            p = rotate_right(p);
        }

        if(bf == -2)
        {
            if (get_height(p->right->left) > get_height(p->right->right))
                p->right = rotate_right(p->right); //big right rotation
            p = rotate_left(p);
        }

        return p; 
    }

public:
    void tree_dump() const
    {
        recursive_print(root);
        std::cout << "\n";
    }

    AVLNode* insert(int k)
    {
        AVLNode* cur{root};
        AVLNode* prev{};

        while(cur)
        {
            prev = cur;
            if (k < cur->key)
                cur = cur->left;
            else if (k > cur->key)
                cur = cur->right;
            else
                return cur;
        }

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

        while(prev)
        {
            fix_height(prev);
            fix_size(prev);
            prev = balance(prev);
            prev = prev->parent;
        }
        
        #if DEBUG
            tree_dump();
        #endif
        return cur;
    }

    AVLNode* find(int k) const
    {
        AVLNode* cur{root};

        while (cur)
        {
            if (k < cur->key)
                cur = cur->left;
            else if (k > cur->key)
                cur = cur->right;
            else
                return cur; 
        }

        return nullptr;
    }

    AVLNode* find_by_number(int k) const
    {
        if (root == nullptr || k > root->size || k <= 0)
            return nullptr;

        int m = k;
        int p = -1;
        AVLNode* cur{root};

        while(p != m)
        {
            p = get_size(cur->left) + 1;

            if (p > m)
                cur = cur->left;
                
            if (p < m)
            {
                cur = cur->right;
                m -= p;
            }
        }

        return cur;
    }

    int distance(int k) const
    {
        int ans{};
        AVLNode* cur{root};

        while(cur)
        {
            if (k < cur->key)
                cur = cur->left;
            else if (k > cur->key)
            {
                ans += get_size(cur->left) + 1;
                cur = cur->right;
            }
            else
            {
                return (ans + get_size(cur->left));
            }
        }

        return ans;
    }
};
}