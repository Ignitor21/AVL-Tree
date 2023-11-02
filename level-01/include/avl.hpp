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
        AVLNode *left, *right;
        bool lthread, rthread;

        bool is_leaf()
        {
            return (lthread && rthread);
        }
    };

    class MyIterator final// pseudo iterator for encapsulating pointers
    {
    private:
        AVLNode *node;
    public:
        explicit MyIterator(AVLNode* ptr) : node(ptr) {}

        const T& operator*() const
        {
            return node->key;
        }
    };          

    AVLNode* root;
    int size;
public:
// big five
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other);
private:
    int balance_factor(const AVLNode* const node) const;
    void fix_height(AVLNode* const node);
    void fix_size(AVLNode* const node);
    AVLNode* rotate_right(AVLNode* const a);
    AVLNode* rotate_left(AVLNode* const a);
    AVLNode* balance(AVLNode* p);
    void TreeDraw(const AVLNode* const node, FILE* const graph_file) const; //for debugging
public:
    MyIterator insert(const T& k);// inserts element in tree, returns iterator 
    //to new element. If element has already been inserted than do nothing anв returns iterator to this element
    MyIterator find(const T& k) const;
    //returns iterator to element with key k, if there is no element with such key, returns nil
    int distance(const T& lower_bound, const T& upper_bound) const;
    //returns number of elements that displaced between lower_bound and upper_bound inclusively. If lower_bound <= upper_bound, returns 0;
    int TreeDump() const; // wrapper for TreeDraw()
    MyIterator begin();
    MyIterator end();
};

template <typename T, typename Comp>
AVLTree<T, Comp>::AVLTree() : root(nullptr), size(0) {}

template <typename T, typename Comp>
AVLTree<T, Comp>::~AVLTree()
{
}

// template <typename T, typename Comp>
// void AVLTree<T, Comp>::TreeDraw(const AVLNode* const node, FILE* const graph_file) const
// {

//     fprintf(graph_file, "   \"%p\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
//                         "   label = \" <value> %d\"];\n", node, node->key);

//     if (node->left != nil)
//     {
//         fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->left);
//         fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->left, node->left->parent);
//     }

//     else if (node->left == nil)
//     {
//         fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
//                             "   label = \" <value> %s\"];\n", node, "left", "nill");
//         fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "left");
//     }

//     if (node->right != nil)
//     {
//         fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->right);
//         fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->right, node->right->parent);
//     }

//     else if (node->right == nil)
//     {
//         fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
//                             "   label = \" <value> %s\"];\n", node, "right", "nill");
//         fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "right");
//     }

//     if (node->left != nil)
//         TreeDraw(node->left, graph_file);

//     if (node->right != nil)
//         TreeDraw(node->right, graph_file);
// }

template <typename T, typename Comp>
AVLTree<T, Comp>::MyIterator AVLTree<T, Comp>::insert(const T& k)
{
    AVLNode* cur{root};

    if (!cur)
    {
        root = new AVLNode{k, 1, nullptr, nullptr, true, true};
        root->left = root;
        root->right = root;

        return MyIterator{root};
    }

    AVLNode* parent{};

    while(!(cur->is_leaf()))
    {
        if ()
    }
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
