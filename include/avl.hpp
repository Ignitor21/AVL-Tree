#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <functional>

/* TO-DO:
- comments
- iterators
- unit tests for big five
*/

namespace avl
{
template <typename T, typename Comp = std::less<T>>
class AVLTree
{
private:
    struct AVLNode
    {
        T key;
        int height; // height of max subtree + 1
        int size; // number of nodes in left subtree + right subtree + 1
        AVLNode *parent, *left, *right;
    };          

    AVLNode* nil;
    AVLNode* root;
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other);

    AVLTree& operator= (const AVLTree& other)
    {
        if (this == &other)
            return *this;

        AVLTree<T, Comp> tmp{other};
        std::swap(root, tmp.root);
        std::swap(nil, tmp.nil);
        return *this;
    }

    AVLTree& operator= (AVLTree&& other)
    {
        if (this == &other)
            return *this;

        std::swap(root, other.root);
        std::swap(nil, other.nil);
        return *this;
    }

private:
    int balance_factor(const AVLNode* const node) const;
    void fix_height(AVLNode* const node);
    void fix_size(AVLNode* const node);
    AVLNode* rotate_right(AVLNode* const a);
    AVLNode* rotate_left(AVLNode* const a);
    AVLNode* balance(AVLNode* p);
    void TreeDraw(const AVLNode* const node, FILE* const graph_file) const;
public:
    AVLNode* insert(const T& k);
    AVLNode* find(const T& k) const;
    AVLNode* find_by_number(const int k) const;
    int less_than(const T& k) const;
    int distance(const T& lower_bound, const T& upper_bound) const;
    int TreeDump() const;
};

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree() : nil(new AVLNode{T{}, 0, 0, nullptr, nullptr, nullptr}), root(nil) 
{
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::~AVLTree()
{
    AVLNode* cur = root;

    while(cur != nil)
    {
        if (cur->left != nil)
            cur = cur->left;
        else if (cur->right != nil)
            cur = cur->right;
        else
        {
            AVLNode* cur_parent = cur->parent;

            if (cur == cur_parent->left)
                cur_parent->left = nil;
            else
                cur_parent->right = nil;

            delete cur;
            cur = cur_parent;
        }
    }

    delete nil;   
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree(const AVLTree& other)
{
    nil = new AVLNode{T{}, 0, 0, nullptr, nullptr, nullptr};
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    AVLNode* other_cur = other.root;
    root = new AVLNode{other_cur->key, other_cur->height, other_cur->size, nil, nil, nil};
    AVLNode *cur = root, *other_nil = other.nil;

    while(other_cur != other.nil)
    {
        if (other_cur->left != other_nil && cur->left == nil)
        {
            cur->left = new AVLNode{other_cur->left->key, other_cur->left->height, other_cur->left->size, cur, nil, nil};
            other_cur = other_cur->left;
            cur = cur->left; 
        }

        else if (other_cur->right != other_nil && cur->right == nil)
        {
            cur->right = new AVLNode{other_cur->right->key, other_cur->right->height, other_cur->right->size, cur, nil, nil};
            other_cur = other_cur->right;
            cur = cur->right;
        }
        else
        {
            other_cur = other_cur->parent;
            cur = cur->parent;
        }
    }
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree(AVLTree&& other)
{
    root = other.root;
    nil = other.nil;
    other.root = nullptr;
    other.nil = nullptr;
}

template <typename T, typename Comp>
int AVLTree<T, Comp>::balance_factor(const AVLNode* const node) const
{
    int left_height = node->left->height;
    int right_height = node->right->height;

    return left_height - right_height;
}

template <typename T, typename Comp>
void AVLTree<T, Comp>::fix_height(AVLNode* const node)
{
    int hl = node->left->height;
    int hr = node->right->height;
    node->height = std::max(hl, hr) + 1;
}

template <typename T, typename Comp>
void AVLTree<T, Comp>::fix_size(AVLNode* const node)
{
    int sl = node->left->size;
    int sr = node->right->size;

    node->size = sl + sr + 1;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::rotate_right(AVLNode* const a)
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

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::rotate_left(AVLNode* const a) 
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

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::balance(AVLNode* p) 
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

template <typename T, typename Comp>
void AVLTree<T, Comp>::TreeDraw(const AVLNode* const node, FILE* const graph_file) const
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

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::insert(const T& k)
{
    AVLNode* cur{root};
    AVLNode* prev{nil};

    while(cur != nil)
    {
        prev = cur;

        if (Comp()(k, cur->key))
            cur = cur->left;
        else if (prev->key == k)
                return prev;
        else
            cur = cur->right;
    }

    cur = new AVLNode{k, 1, 1, nil, nil, nil};

    if(prev == nil)
    {
        root = cur;
        return cur;
    }

    if (Comp()(k, prev->key))
        prev->left = cur;
    else
        prev->right = cur;

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

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::find(const T& k) const
{
    AVLNode* cur{root};

    while (cur != nil)
    {
        if (Comp()(k, cur->key))
            cur = cur->left;
        else if (cur->key == k)
            return cur;
        else
            cur = cur->right;
    }

    return nil;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::find_by_number(const int k) const
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

template <typename T, typename Comp>
int AVLTree<T, Comp>::less_than(const T& k) const
{
    int ans{};
    AVLNode* cur{root};

    while(cur != nil)
    {
        if (Comp()(k, cur->key))
            cur = cur->left;
        else if (cur->key == k)
            return (ans + cur->left->size);
        else
        {
            ans += cur->left->size + 1;
            cur = cur->right;
        }
    }

    return ans;
}

template <typename T, typename Comp>
int AVLTree<T, Comp>::distance(const T& lower_bound, const T& upper_bound) const
{
    if (lower_bound >= upper_bound)
        return 0;

    T lb = lower_bound;
    T ub = upper_bound;
    int ans{root->size};
    AVLNode* cur{root};

    bool is_inverse = !Comp()(lb, ub);
    if (is_inverse)
        std::swap(lb, ub);

    while(cur != nil)
    {
        if (Comp()(cur->key, ub))
            cur = cur->right;
        else if (cur->key == ub)
        {
            ans -= cur->right->size;
            break;
        }
        else
        {
            ans -= cur->right->size + 1;
            cur = cur->left;
        }    
    }

    cur = root;
    while (cur != nil)
    {
        if (Comp()(lb, cur->key))
            cur = cur->left;
        else if (lb == cur->key)
        {
            ans -= cur->left->size;
            break;
        }
        else
        {
            ans -= cur->left->size + 1;
            cur = cur->right;
        }
    }

    if (is_inverse)
        std::swap(lb, ub);
        
    return ans;
}

template <typename T, typename Comp>
int AVLTree<T, Comp>::TreeDump() const
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

