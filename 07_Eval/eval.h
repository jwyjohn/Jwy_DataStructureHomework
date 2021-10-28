#ifndef _EVAL_H__
#define _EVAL_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class exp
{

    string raw_exp;
    const string nums = "0123456789";
    const string ops = "*+-";
    const string parms = "()";
    struct Atom
    {
        bool isOp;
        int val;
        char op;
        Atom(bool isOp, int val, char op) : isOp(isOp), val(val), op(op){};
    };
    struct Node
    {
        bool isParm;
        Atom data;
        char op;
        Node *lchild, *rchild;
        Node(Atom data) : data(data){};
    };
    struct numStack
    {
        int s[1024];
        int ptr = 0;
        bool isEmpty() { return (ptr == 0); }
        bool isFull() { return (ptr == 1023); }
        int push(int x)
        {
            if (!isFull())
            {
                ptr++;
                s[ptr] = x;
            }
            else
                return -1;
            return 0;
        };
        int pop()
        {
            int ret = -1;
            if (!isEmpty())
            {
                ret = s[ptr];
                ptr--;
            };
            return ret;
        };
    };
    struct opStack
    {
        char s[1024];
        int ptr = 0;
        bool isEmpty() { return (ptr == 0); }
        bool isFull() { return (ptr == 1023); }
        int push(char x)
        {
            if (!isFull())
            {
                ptr++;
                s[ptr] = x;
            }
            else
                return -1;
            return 0;
        };
        char pop()
        {
            char ret = 'N';
            if (!isEmpty())
            {
                ret = s[ptr];
                ptr--;
            };
            return ret;
        };
    };

public:
    exp(string t) : raw_exp(t)
    {
        numStack ns;
        opStack os;
        for (auto ch : t)
        {
            bool isOp = (ops.find(ch) != ops.npos);
            bool isNum = (nums.find(ch) != nums.npos);
            bool isParm = (parms.find(ch) != parms.npos);
            if (!(isOp || isNum || isParm))
            {
                cout << "Invalid Char." << endl;
            } else {
                if (isNum) ns.push(nums.find(ch));
                if (isOp) os.push(ch);
            };
        };
        while (!ns.isEmpty() && !os.isEmpty()){
            int a,b,sum;
            a=ns.pop();
            b=ns.pop();
            sum = a+b;
            ns.push(sum);
            cout<<a<<os.pop()<<b<<'='<<sum<<endl;
        };
    };
};

#endif