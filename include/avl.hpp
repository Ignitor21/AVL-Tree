#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <functional>

namespace avl
{
template <typename T, typename Comp = std::less<T>>
class AVLTree final
{
private:
    struct AVLNode final
    {
        T key;
        int height; // height of max subtree + 1
        int size; // number of nodes in left subtree + right subtree + 1
        AVLNode *left, *right;
        bool rthread, lthread;
    };

    class MyIterator final// pseudo iterator for encapsulating pointers
    {
    private:
        AVLNode *node;
    public:
        explicit MyIterator(AVLNode* ptr) : node(ptr) {}

        const T& operator*() const
        {
            if (node->size == 0)
            {
                std::cerr << "Bruh, man, stop dereferencing invalid pointers!\n";
                abort();
            }

            return node->key;
        }

        MyIterator& operator++()
        {
            AVLNode* next = node->right;

            if(node->rthread)
            {
                node = next;
                return *this;
            }
            
            while (!next->lthread)
            {
                next = next->left;
            }

            node = next;
            return *this;
        }

        MyIterator operator++(int)
        {
            MyIterator tmp{*this};
            ++(*this);
            return tmp;
        }

        bool operator ==(const MyIterator& rhs) const
        {
            return (node == rhs.node);
        }

        bool operator !=(const MyIterator& rhs) const
        {
            return (node != rhs.node);
        }
    };          

    AVLNode* nil;
    AVLNode* root;
public:
// big five
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
    AVLNode* parent(AVLNode* const node) const;
    bool is_leaf(const AVLNode* const node) const;
    int balance_factor(const AVLNode* const node) const;
    void fix_height(AVLNode* const node);
    void fix_size(AVLNode* const node);
    AVLNode* rotate_right(AVLNode* const a);
    AVLNode* rotate_left(AVLNode* const a);
    AVLNode* balance(AVLNode* p);
    void TreeDraw(const AVLNode* const node, FILE* const graph_file) const; //for debugging
public:
    MyIterator insert(const T& k);// inserts element in tree, returns iterator 
    //to new element. If element has already been inserted than do nothing and returns iterator to this element
    MyIterator find(const T& k) const;
    //returns iterator to element with key k, if there is no element with such key, returns nil
    MyIterator find_by_number(const int k) const;
    //finds the biggest k-th element in tree. If k <= 0 or k > size of tree, returns nil 
    int less_than(const T& k) const;
    // returns number of element with key that less than k 
    int distance(const T& lower_bound, const T& upper_bound) const;
    //returns number of elements that displaced between lower_bound and upper_bound inclusively. If lower_bound <= upper_bound, returns 0;
    int TreeDump() const; // wrapper for TreeDraw()
    MyIterator begin();
    MyIterator end();
};

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree() : nil(new AVLNode{T{}, 0, 0, nullptr, nullptr, true, true}), root(nil)
{
    nil->left = nil;
    nil->right = nil;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::~AVLTree()
{
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree(const AVLTree& other)
{
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
bool AVLTree<T, Comp>::is_leaf(const AVLNode* const node) const
{
    return (node->lthread && node->rthread);
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::parent(AVLNode* const node) const
{
    if (node == root)
        return nil;
    
    AVLNode* left_suc = node;
    AVLNode* right_suc = node;

    while (!left_suc->lthread)
        left_suc = left_suc->left;
    left_suc = left_suc->left;

    if (left_suc->right == node)
        return left_suc;
    
    while(!right_suc->rthread)
        right_suc = right_suc->right;
    right_suc = right_suc->right;

    if (right_suc->left == node)
        return right_suc;
    else
    {
        std::cout << "Error in tree\n";
        abort();
    }
}

template <typename T, typename Comp>
int AVLTree<T, Comp>::balance_factor(const AVLNode* const node) const
{
    int left_height = node->lthread ? 0 : node->left->height;
    int right_height = node->rthread ? 0 :  node->right->height;

    return left_height - right_height;
}

template <typename T, typename Comp>
void AVLTree<T, Comp>::fix_height(AVLNode* const node)
{
    int hl = node->lthread ? 0 : node->left->height;
    int hr = node->rthread ? 0 : node->right->height;
    node->height = std::max(hl, hr) + 1;
}

template <typename T, typename Comp>
void AVLTree<T, Comp>::fix_size(AVLNode* const node)
{
    int sl = node->lthread ? 0 : node->left->size;
    int sr = node->rthread ? 0 : node->right->size;
    node->size = sl + sr + 1;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::rotate_right(AVLNode* const a)
{
    AVLNode* b{a->left};
    AVLNode* a_parent{parent(a)};

    if(b->rthread)
        a->left = b;
    else
        a->left = b->right;
    a->lthread = b->rthread;
    b->right = a;
    b->rthread = false;

    if (a_parent->right == a)
        a_parent->right = b;
    else
        a_parent->left = b;

    if (a == root)
        root = b;

    fix_height(a);
    fix_height(b);
    fix_size(a);
    fix_size(b);
    return b;
}

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLNode* AVLTree<T, Comp>::rotate_left(AVLNode* const a) 
{
    AVLNode* b{a->right};
    AVLNode* a_parent{parent(a)};

    if (b->lthread)
        a->right = b;
    else
        a->right = b->left;
    a->rthread = b->lthread;
    b->left = a;
    b->lthread = false; 

    if (a_parent->left == a)
        a_parent->left = b;
    else
        a_parent->right = b;

    if (a == root)
        root = b;

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
        int c_height = p->left->rthread ? 0 : p->left->right->height;
        int L_height = p->left->lthread ? 0 : p->left->left->height;
        if (c_height > L_height)
            p->left = rotate_left(p->left); //big right rotation
        p = rotate_right(p);
    }

    if(bf == -2)
    {
        int c_height = p->right->lthread ? 0 : p->right->left->height;
        int R_height = p->right->rthread ? 0 : p->right->right->height;
        if (c_height > R_height)
            p->right = rotate_right(p->right); //big left rotation
        p = rotate_left(p);
    }
    return p; 
}

template <typename T, typename Comp>
void AVLTree<T, Comp>::TreeDraw(const AVLNode* const node, FILE* const graph_file) const
{
    fprintf(graph_file, "   \"%p\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
                        "   label = \" <value> %d\"];\n", node, node->key);

    if (!node->lthread)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->left);
    }

    else
    {
        if (node->left != nil)
            fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\", style=dotted];\n", node, node->left);
        else
            fprintf(graph_file, "  \"%p\" -> \"%s\" [color = \"green\", style=dotted];\n", node, "nil");
    }

    if (!node->rthread)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->right);
    }

    else
    {
        if (node->right != nil)
            fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\", style=dotted];\n", node, node->right);
        else
            fprintf(graph_file, "  \"%p\" -> \"%s\" [color = \"green\", style=dotted];\n", node, "nil");
    }

    if (!node->lthread)
        TreeDraw(node->left, graph_file);

    if (!node->rthread)
        TreeDraw(node->right, graph_file);
}

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::insert(const T& key)
{
    AVLNode *cur{root}; 
    AVLNode *prev{nil};

    while (cur != nil) 
    { 
        prev = cur;

        if (key == cur->key) 
        {  
            return MyIterator{cur}; 
        } 
  
        if (Comp()(key, cur->key)) 
        { 
            if (cur->lthread == false) 
                cur = cur -> left; 
            else
                break; 
        } 

        else
        { 
            if (cur->rthread == false) 
                cur = cur->right; 
            else
                break; 
        } 
    } 
  
    AVLNode *tmp = new AVLNode{key, 1, 1, nil, nil, true, true}; 
      
    if (prev == nil) 
    { 
        root = tmp; 
        tmp -> left = nil; 
        tmp -> right = nil; 
    } 

    else if (Comp()(key, prev->key)) 
    { 
        tmp->left = prev->left; 
        tmp->right = prev; 
        prev->lthread = false; 
        prev->left = tmp; 
    } 
    else
    { 
        tmp->left = prev; 
        tmp->right = prev->right; 
        prev->rthread = false; 
        prev->right = tmp; 
    } 

    while(prev != nil)
    {
        fix_height(prev);
        fix_size(prev);
        prev = balance(prev);
        prev = parent(prev);
    }
    
    return MyIterator{tmp};
}

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::find(const T& k) const
{
    AVLNode* cur{root};

    while (cur != nil)
    {
        if (Comp()(k, cur->key))
            cur = cur->left;
        else if (cur->key == k)
            return MyIterator{cur};
        else
            cur = cur->right;
    }

    return MyIterator{nil};
}

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::find_by_number(const int k) const
{
    if ((root == nil || k > root->size || k <= 0))
    {
        #if DEBUG
            std::cout << "Invalid number: " << k << "\n";
            std::cout << "Size of tree: " << root->size << "\n";
        #endif
        return MyIterator{nil};
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

    return MyIterator{cur};
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

    for(;;)
    {
        if (Comp()(cur->key, ub))
        {
            if (!cur->rthread)
                cur = cur->right;
            else
                break;
        }
        else if (cur->key == ub)
        {
            if (!cur->rthread)
                ans -= cur->right->size;
            break;
        }
        else
        {
            if (!cur->rthread)
                ans -= cur->right->size + 1;
            if (!cur->lthread)
                cur = cur->left;
            else
                break;
        }    
    }

    cur = root;
    for (;;)
    {
        if (Comp()(lb, cur->key))
        {
            if (!cur->lthread)
                cur = cur->left;
            else
                break;
        }
        else if (lb == cur->key)
        {
            if (!cur->lthread)
                ans -= cur->left->size;
            break;
        }
        else
        {
            if (!cur->lthread)
                ans -= cur->left->size + 1;
            if (!cur->rthread)
                cur = cur->right;
            else
                break;
        }
    }

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

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::begin() 
{
    if (root == nil)
        return MyIterator{root};

    AVLNode* cur = root;

    while(cur->left != nil)
    {
        cur = cur->left;
    }

    return MyIterator{cur};
}

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::end()
{
    return MyIterator{nil};
} 

}
