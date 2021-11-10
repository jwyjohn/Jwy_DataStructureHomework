#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>
#include <assert.h>

using namespace std;

typedef struct avl_tree_node
{
    int data = 0;
    int height = 0;
    avl_tree_node *left = nullptr;
    avl_tree_node *right = nullptr;

} avl_tree;

int print_tree_lvr(avl_tree *t)
{

    if (t->left != nullptr)
    {
        print_tree_lvr(t->left);
    };
    if (t->data != 0)
        cout << " " << t->data;
    if (t->right != nullptr)
    {
        print_tree_lvr(t->right);
    };
    return 0;
};

int print_tree_vlr(avl_tree *t)
{
    if (t->data != 0)
        cout << " " << t->data;
    if (t->left != nullptr)
    {
        print_tree_vlr(t->left);
    };

    if (t->right != nullptr)
    {
        print_tree_vlr(t->right);
    };
    return 0;
};

int get_balance(avl_tree *t)
{
    if (t->left == nullptr && t->right == nullptr)
        return 0;
    if (t->left == nullptr && t->right != nullptr)
        return t->right->height;
    if (t->left != nullptr && t->right == nullptr)
        return -1 * t->left->height;
    return (t->right->height - t->left->height);
};

int get_height(avl_tree *t)
{
    int hl = 0, hr = 0;
    if (t->left == nullptr)
        hl = 0;
    else
        hl = t->left->height + 1;
    if (t->right == nullptr)
        hr = 0;
    else
        hr = t->right->height + 1;
    return max(hl, hr);
};

int rotate_left(avl_tree *t, avl_tree *&p)
{
    p = t->right;
    avl_tree *tmp;
    tmp = t->right;
    t->right = t->right->left;
    tmp->left = t;
    return 0;
};

int rotate_right(avl_tree *t, avl_tree *&p)
{
    p = t->left;
    avl_tree *tmp;
    tmp = t->left;
    t->left = t->left->right;
    tmp->right = t;
    return 0;
};

int adjust_tree_LL(avl_tree *t, avl_tree *&p)
{
    rotate_right(t, p);
    return 0;
};

int adjust_tree_RR(avl_tree *t, avl_tree *&p)
{
    rotate_left(t, p);
    return 0;
};

int adjust_tree_LR(avl_tree *t, avl_tree *&p)
{
    rotate_left(t->left, t->left);
    rotate_right(t, p);
    return 0;
};

int adjust_tree_RL(avl_tree *t, avl_tree *&p)
{
    rotate_right(t->right, t->right);
    rotate_left(t, p);
    return 0;
};

int main()
{
    avl_tree T[1000];
    for (int i = 0; i < 31; i++)
    {
        T[i].data = i + 1;
        T[i].left = &T[i * 2 + 1];
        T[i].right = &T[i * 2 + 2];
    };
    print_tree_lvr(&T[0]);
    cout << endl;
    print_tree_vlr(&T[0]);
    cout << endl;

    adjust_tree_LR(T[0].left, T[0].left);
    print_tree_lvr(&T[0]);
    cout << endl;
    print_tree_vlr(&T[0]);
    cout << endl;
    return 0;
};