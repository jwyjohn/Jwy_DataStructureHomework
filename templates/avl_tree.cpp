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

int print_tree(avl_tree *t)
{

    if (t->left != nullptr)
    {
        print_tree(t->left);
    };
    if (t->data != 0)
        cout << " " << t->data;
    if (t->right != nullptr)
    {
        print_tree(t->right);
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

int rotate_left(avl_tree *p, avl_tree *t)
{
    p->right = t->right;
    avl_tree *tmp;
    tmp = t->right;
    t->right = t->right->left;
    tmp->left = t;
    return 0;
};

int rotate_right(avl_tree *p, avl_tree *t)
{
    p->left = t->left;
    avl_tree *tmp;
    tmp = t->left;
    t->left = t->left->right;
    tmp->right = t;
    return 0;
};

int main()
{
    avl_tree T[100];
    for (int i = 0; i < 15; i++)
    {
        T[i].data = i + 1;
        T[i].left = &T[i * 2 + 1];
        T[i].right = &T[i * 2 + 2];
    };
    print_tree(&T[0]);
    cout << endl;

    rotate_right(&T[0], &T[1]);
    print_tree(&T[0]);
    cout << endl;

    rotate_left(&T[3], &T[1]);
    print_tree(&T[0]);
    cout << endl;
    return 0;
};