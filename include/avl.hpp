#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>

/* TO-DO:
- big five
- comments
- iterators
- comparator
- templates
- get rid of recursion
*/

namespace avl
{
class AVLTree
{
private:
    struct AVLNode
    {
        int key;
        int height; // height of max subtree + 1
        int size; // number of nodes in left subtree + right subtree + 1
        AVLNode *parent, *left, *right;
    };          

    AVLNode* nil;
    AVLNode* root;
public:
    AVLTree();
    ~AVLTree();
private:
    int balance_factor(AVLNode* node) const;
    void fix_height(AVLNode* node);
    void fix_size(AVLNode* node);
    void FreeAVLTree(AVLNode* node);
    void recursive_print(AVLNode* node) const;
    AVLNode* rotate_right(AVLNode* a);
    AVLNode* rotate_left(AVLNode* a);
    AVLNode* balance(AVLNode* p);
    void TreeDraw(AVLNode* node, FILE *graph_file) const;
public:
    void dump() const;
    AVLNode* insert(int k);
    AVLNode* find(int k) const;
    AVLNode* find_by_number(int k) const;
    int less_then(int k) const;
    int distance(int lb, int ub) const;
    int TreeDump() const;
};

AVLTree::AVLTree() : nil(new AVLNode{0, 0, 0, nullptr, nullptr, nullptr}), root(nil) 
{
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
}

AVLTree::~AVLTree()
{
    FreeAVLTree(root);
    delete nil;
}

int AVLTree::balance_factor(AVLNode* node) const
{
    int left_height = node->left->height;
    int right_height = node->right->height;

    return left_height - right_height;
}

void AVLTree::fix_height(AVLNode* node)
{
    int hl = node->left->height;
    int hr = node->right->height;
    node->height = std::max(hl, hr) + 1;
}

void AVLTree::fix_size(AVLNode* node)
{
    int sl = node->left->size;
    int sr = node->right->size;

    node->size = sl + sr + 1;
}

void AVLTree::FreeAVLTree(AVLNode* node) 
{
    if(node != nil)
    {
        FreeAVLTree(node->left);
        FreeAVLTree(node->right);
        delete node;
    }
}

void AVLTree::recursive_print(AVLNode* node) const
{
    if (node != nil) 
    { 
        recursive_print(node->left);
        std::cout << node->key << '(' << balance_factor(node) << ", " << node->size << ") "; 
        recursive_print(node->right); 
    }
}

AVLTree::AVLNode* AVLTree::rotate_right(AVLNode* a)
{
    if (a == nil)
        return a;

    AVLNode* b = a->left;
    a->left = b->right;
    b->right = a;
    b->parent = a->parent;
    a->parent = b;

    if (b->parent == nil)
        root = b;
    else
    {
        if (b->parent->left == a)
            b->parent->left = b;
        else
            b->parent->right = b;
    }

    if (a->left != nil)
        a->left->parent = a;

    fix_height(a);
    fix_height(b);
    fix_size(a);
    fix_size(b);
    return b;
}

AVLTree::AVLNode* AVLTree::rotate_left(AVLNode* a) 
{
    if (a == nil)
        return a;

    AVLNode* b = a->right;
    a->right = b->left;
    b->left = a;
    b->parent = a->parent;
    a->parent = b;

    if (b->parent == nil)
        root = b;
    else
    {
        if (b->parent->left == a)
            b->parent->left = b;
        else
            b->parent->right = b;
    }

    if (a->right != nil)
        a->right->parent = a;

    fix_height(a);
    fix_height(b);
    fix_size(a);
    fix_size(b);
    return b; 
}

AVLTree::AVLNode* AVLTree::balance(AVLNode* p) 
{
    int bf = balance_factor(p);
    if(bf == 2)
    {
        if (p->left->right->height > p->left->left->height)
            p->left = rotate_left(p->left); //big left rotation
        p = rotate_right(p);
    }

    if(bf == -2)
    {
        if (p->right->left->height > p->right->right->height)
            p->right = rotate_right(p->right); //big right rotation
        p = rotate_left(p);
    }
    return p; 
}

void AVLTree::TreeDraw(AVLNode* node, FILE *graph_file) const
{

    fprintf(graph_file, "   \"%p\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
                        "   label = \" <value> %d\"];\n", node, node->key);

    if (node->left != nil)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->left);
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->left, node->left->parent);
    }

    else if (node->left == nil)
    {
        fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" <value> %s\"];\n", node, "left", "nill");
        fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "left");
    }

    if (node->right != nil)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->right);
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->right, node->right->parent);
    }

    else if (node->right == nil)
    {
        fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" <value> %s\"];\n", node, "right", "nill");
        fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "right");
    }

    if (node->left != nil)
        TreeDraw(node->left, graph_file);

    if (node->right != nil)
        TreeDraw(node->right, graph_file);
}

void AVLTree::dump() const
{
    recursive_print(root);
    std::cout << "\n";
}

AVLTree::AVLNode* AVLTree::insert(int k)
{
    AVLNode* cur{root};
    AVLNode* prev{nil};

    while(cur != nil)
    {
        prev = cur;
        if (k < cur->key)
            cur = cur->left;
        else if (k > cur->key)
            cur = cur->right;
        else
            return cur;
    }

    cur = new AVLNode{k, 1, 1, nil, nil, nil};

    if(prev == nil)
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

    while(prev != nil)
    {
        fix_height(prev);
        fix_size(prev);
        prev = balance(prev);
        prev = prev->parent;
    }
    return cur;
}


AVLTree::AVLNode* AVLTree::find(int k) const
{
    AVLNode* cur{root};

    while (cur != nil)
    {
        if (k < cur->key)
            cur = cur->left;
        else if (k > cur->key)
            cur = cur->right;
        else
            return cur; 
    }

    return nil;
}

AVLTree::AVLNode* AVLTree::find_by_number(int k) const
{
    if ((root == nil || k > root->size || k <= 0))
    {
        #if DEBUG
            std::cout << "Invalid number: " << k << "\n";
            std::cout << "Size of tree: " << root->size << "\n";
        #endif
        return nil;
    }

    int m = k;
    int p = -1;
    AVLNode* cur{root};

    while(p != m)
    {
        p = cur->left->size + 1;

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

int AVLTree::less_then(int k) const
{
    int ans{};
    AVLNode* cur{root};

    while(cur != nil)
    {
        if (k < cur->key)
            cur = cur->left;
        else if (k > cur->key)
        {
            ans += cur->left->size + 1;
            cur = cur->right;
        }
        else
        {
            return (ans + cur->left->size);
        }
    }

    return ans;
}

int AVLTree::distance(int lb, int ub) const
{
    if (lb >= ub)
        return 0;

    int ans{root->size};
    AVLNode* cur{root};

    while(cur != nil)
    {
        if (ub > cur->key)
            cur = cur->right;
        else if (ub < cur->key)
        {
            ans -= cur->right->size + 1;
            cur = cur->left;
        }    
        else
        {
            ans -= cur->right->size;
            break;
        }
    }

    cur = root;
    while (cur != nil)
    {
        if (lb < cur->key)
            cur = cur->left;
        else if (lb > cur->key)
        {
            ans -= cur->left->size + 1;
            cur = cur->right;
        }
        else
        {
            ans -= cur->left->size;
            break;
        }
    }

    return ans;
}

int AVLTree::TreeDump() const
{

    FILE *graph_file = fopen("../../graphics/graph.dot", "w");

    if (graph_file == nullptr)
    {
        std::cerr << "Failed openning graph file in " << __PRETTY_FUNCTION__ << std::endl;
        return -1; 
    }

    fprintf(graph_file, "digraph Tree\n{\n");
    fprintf(graph_file, "   rankdir = HR;\n");
    fprintf(graph_file, "   node[fontsize=14];\n   edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n");
    fprintf(graph_file, "   tree[shape = Mrecord, style = filled, fillcolor = \"chartreuse1\", "
                        "label = \"My Tree | size = %u\"];\n", root->size);
    TreeDraw(root, graph_file);
    fprintf(graph_file, "   tree -> \"%p\" [color = \"gray0\"];\n", root);
    fprintf(graph_file, "}");

    if (fclose(graph_file) == EOF)
    {
        std::cerr << "Failed closing graph.dot in function " << __PRETTY_FUNCTION__ << std::endl;
        return -1;
    }

    char call_graph[100] = " ";

    static int graph_num = 1;
    sprintf(call_graph, "dot ../../graphics/graph.dot -Tpng -o ../../graphics/graph%d.png", graph_num++);
    
    std::system(call_graph);

    return 0;
}

}

