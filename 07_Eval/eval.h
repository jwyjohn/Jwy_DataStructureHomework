#ifndef _EVAL_H__
#define _EVAL_H__

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
map<char, char> op_map = {
    {'(', 'L'},
    {')', 'R'},
    {'*', 'M'},
    {'/', 'D'},
    {'+', 'A'},
    {'-', 'S'},
    {'0', 'N'},
    {'1', 'N'},
    {'2', 'N'},
    {'3', 'N'},
    {'4', 'N'},
    {'5', 'N'},
    {'6', 'N'},
    {'7', 'N'},
    {'8', 'N'},
    {'9', 'N'},
};
struct node
{
    char kind;
    int val;
};
node char_to_node(char ch)
{
    assert(op_map.find(ch) != op_map.end());
    node ret;
    ret.val = (op_map[ch] == 'N') ? int(ch - '0') : -1;
    ret.kind = op_map[ch];
    return ret;
};

#endif