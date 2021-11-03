#ifndef _BT_H__
#define _BT_H__

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

template <class T>
struct bt_node
{
    T val;
    bt_node *lc = NULL, *rc = NULL;
};

template <class T>
bt_node<T> *create_bt(T val)
{
    bt_node<T> *ret = new bt_node<T>;
    ret->val = val;
    return ret;
};

template <class T>
bt_node<T> *find_bt(bt_node<T> *root, T val)
{
    if (root->lc != NULL && root->val > val)
        return find_bt(root->lc, val);
    if (root->rc != NULL && val > root->val)
        return find_bt(root->rc, val);
    cout << "Node " << val << " not found." << endl;
    return NULL;
};

template <class T>
int insert_bt(bt_node<T> *root, T val)
{
    if (find_bt(root, val) != NULL)
    {
        cout << "Node " << val << " exists." << endl;
        return 1;
    }
    else
    {
        bt_node<T> *res = new bt_node<T>;
        res->val = val;
        bt_node<T> *pos = root;
        while ((pos->lc != NULL && pos->val > val) || (pos->rc != NULL && val > pos->val))
        {
            if (pos->lc != NULL && pos->val > val)
                pos = pos->lc;
            if (pos->rc != NULL && val > pos->val)
                pos = pos->rc;
        };
        if (pos->lc == NULL && pos->val > val)
            pos->lc = res;
        if (pos->rc == NULL && val > pos->val)
            pos->rc = res;
        return 0;
    };
};
template <class T>
int print_bt(bt_node<T> *root)
{

    if (root->lc != NULL)
        print_bt(root->lc);
    cout << " " << root->val;
    if (root->rc != NULL)
        print_bt(root->rc);
    return 0;
};

#endif