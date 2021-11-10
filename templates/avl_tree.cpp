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
    bool lazy = false;
    avl_tree_node *left = nullptr;
    avl_tree_node *right = nullptr;

} avl_tree;

avl_tree T;
avl_tree *root = &T;

int get_balance(avl_tree *t);
int get_height(avl_tree *t);
int get_height_s(avl_tree *t);

int print_tree_lvr(avl_tree *t)
{

    if (t->left != nullptr)
    {
        print_tree_lvr(t->left);
    };
    if (t->data != 0)
        // cout << " " << t->data << "[" << get_balance(t) << "," << get_height(t) << "," << get_height_s(t) << "]";
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
        // cout << " " << t->data << "[" << get_balance(t) << "," << get_height(t) << "," << get_height_s(t) << "]";
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

// int get_height(avl_tree *t)
// {
//     if (t == nullptr)
//         return 0;
//     return max(get_height(t->left), get_height(t->right)) + 1;
// };

int get_height_s(avl_tree *t)
{
    if (t == nullptr)
        return 0;
    return max(get_height_s(t->left), get_height_s(t->right)) + 1;
};

int get_height(avl_tree *t)
{
    if (t == nullptr)
        return 0;
    if (t->lazy == true)
        return t->height;
    else
    {
        t->height = max(get_height_s(t->left), get_height_s(t->right)) + 1;
        // t->height = max(get_height(t->left), get_height(t->right)) + 1;
        t->lazy = true;
    }
    return t->height;
};

int get_balance(avl_tree *t)
{
    if (t == nullptr)
        return 0;
    // return get_height(t->right) - get_height(t->left);
    return get_height_s(t->right) - get_height_s(t->left);
};

avl_tree *rotate_left(avl_tree *t)
{
    avl_tree *root;
    root = t->right;
    t->right = t->right->left;
    root->left = t;
    return root;
};

avl_tree *rotate_right(avl_tree *t)
{
    avl_tree *root;
    root = t->left;
    t->left = t->left->right;
    root->right = t;
    return root;
};

avl_tree *adjust_tree_RR(avl_tree *t)
{
    return rotate_right(t);
};

avl_tree *adjust_tree_LL(avl_tree *t)
{
    return rotate_left(t);
};

avl_tree *adjust_tree_LR(avl_tree *t)
{
    avl_tree *root;
    t->left = rotate_left(t->left);
    root = rotate_right(t);
    return root;
};

avl_tree *adjust_tree_RL(avl_tree *t)
{
    avl_tree *root;
    t->right = rotate_right(t->right);
    root = rotate_left(t);
    return root;
};

int balance_node(avl_tree *&t)
{
    int bf = get_balance(t);
    if (bf > 1)
    {
        if (get_balance(t->right) > 0)
        {
            t = adjust_tree_LL(t);
        }
        else
        {
            t = adjust_tree_RL(t);
        };
    }
    else if (bf < -1)
    {
        if (get_balance(t->left) < 0)
        {
            t = adjust_tree_RR(t);
        }
        else
        {
            t = adjust_tree_LR(t);
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
    return nullptr;
};

int insert_val(avl_tree *&t, int val)
{
    t->lazy = false;
    if (t->data == val)
    {
        // cout << "Value exists!" << endl;
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
    balance_node(t);
    return 0;
};

int remove_val(avl_tree *&t, int val)
{
    t->lazy = false;
    if (t->data == val)
    {
        if (t->left == nullptr && t->right == nullptr)
        {
            avl_tree *to_del = t;
            t = nullptr;
            delete to_del;
            return 0;
        }
        else if (t->left != nullptr && t->right == nullptr)
        {
            avl_tree *to_del = t;
            t = t->left;
            delete to_del;
            return 0;
        }
        else if (t->right != nullptr && t->left == nullptr)
        {
            avl_tree *to_del = t;
            t = t->right;
            delete to_del;
            return 0;
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            avl_tree *left_max = t->left, *pre_max = nullptr;
            while (left_max->right != nullptr)
            {
                pre_max = left_max;
                left_max = left_max->right;
            }
            t->data = left_max->data;
            if (left_max == t->left)
            {
                t->left = left_max->left;
            }
            else
            {
                pre_max->right = left_max->left;
            };
            delete left_max;
            return 0;
        };
    }
    else
    {
        if (val < t->data)
        {
            if (t->left == nullptr)
            {
                // cout<<"Value not found!"<<endl;
                return 1;
            }
            else
            {
                remove_val(t->left, val);
            }
        };
        if (val > t->data)
        {
            if (t->right == nullptr)
            {
                // cout<<"Value not found!"<<endl;
                return 1;
            }
            else
            {
                remove_val(t->right, val);
            }
        };
    };
    balance_node(t);
    return 0;
};

int main()
{
    int i = 0;
    int op, N;
    while (true)
    {
        cin >> op >> N;
        if (op == 1)
            insert_val(root, N);
        if (op == 2)
            remove_val(root, N);
        // print_tree_lvr(root);
        // cout << endl;
        print_tree_vlr(root);
        cout << endl;
    }

    return 0;
};
