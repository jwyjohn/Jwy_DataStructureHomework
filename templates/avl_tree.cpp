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

int get_height(avl_tree *t)
{
    if (t == nullptr)
        return 0;
    return max(get_height(t->left), get_height(t->right)) + 1;
};

int get_balance(avl_tree *t)
{
    if (t == nullptr)
        return 0;
    // return (t->right->height - t->left->height);
    return get_height(t->right) - get_height(t->left);
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

int adjust_tree_RR(avl_tree *t, avl_tree *&p)
{
    rotate_right(t, p);
    return 0;
};

int adjust_tree_LL(avl_tree *t, avl_tree *&p)
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

int balance_node(avl_tree *t, avl_tree *&p)
{
    int bf = get_balance(t);
    if (bf > 1)
    {
        if (get_balance(t->right) > 0)
        {
            adjust_tree_LL(t, p);
        };
        if (get_balance(t->right) <= 0)
        {
            adjust_tree_RL(t, p);
        };
    };
    if (bf < -1)
    {
        if (get_balance(t->left) > 0)
        {
            adjust_tree_RR(t, p);
        };
        if (get_balance(t->left) <= 0)
        {
            adjust_tree_LR(t, p);
        };
    };
    return 0;
};

avl_tree *find_val(avl_tree *t, int val)
{
    if (val == t->data)
        return t;
    if (val < t->data)
    {
        if (t->left == nullptr)
            return t;
        else
            return find_val(t->left, val);
    };
    if (val > t->data)
    {
        if (t->right == nullptr)
            return t;
        else
            return find_val(t->right, val);
    };
};

int insert_val(avl_tree *t, int val)
{
    if (t->data == val)
    {
        cout << "Value exists!" << endl;
        return 1;
    }
    else
    {
        if (val < t->data)
        {
            if (t->left == nullptr)
            {
                avl_tree_node *ins = new avl_tree_node;
                ins->data = val;
                t->left = ins;
            }
            else
            {
                insert_val(t->left, val);
            }
        };
        if (val > t->data)
        {
            if (t->right == nullptr)
            {
                avl_tree_node *ins = new avl_tree_node;
                ins->data = val;
                t->right = ins;
            }
            else
            {
                insert_val(t->right, val);
            }
        };
    };
    balance_node(t->left, t->left);
    balance_node(t->right, t->right);
    return 0;
};

int main()
{
    avl_tree T[1000];
    int i = 0;
    int N;
    cin >> N;
    T[0].data = N;
    while (true)
    {
        cin >> N;
        insert_val(&T[0], N);
        print_tree_lvr(&T[0]);
        cout << endl;
        print_tree_vlr(&T[0]);
        cout << endl;
    }

    return 0;
};