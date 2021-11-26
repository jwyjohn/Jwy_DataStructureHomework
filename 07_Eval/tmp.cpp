#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

// 判断是否为括号
bool isPra(char c)
{
    return (c == '(' || c == ')') ? true : false;
};

// 获得符号的优先性
int getPri(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 0; // 如果是加减，返回0
        break;
    case '*':
    case '/':
        return 1; // 如果是乘除，返回1
        break;
    case '(':
    case ')':
        return -1; // 这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号
        break;
    default:
        cout << "ERROR\n"
             << endl;
    };
};

//判断符号的优先性
void check(char c, stack<char> &operator_s, string &suffix)
{
    if (operator_s.empty())
    {
        operator_s.push(c);
        return;
    }

    if (isPra(c))
    {
        if (c == '(')
        {
            operator_s.push(c);
        }
        else
        {
            // 弹出所有元素直到遇到左括号
            while (operator_s.top() != '(')
            {
                suffix += operator_s.top();
                operator_s.pop();
            }

            // 遇到左括号，弹出且不加入后缀表达式
            operator_s.pop();
        }
    }
    else
    {
        // 如果不是括号，比较当前元素，与栈顶元素的优先级
        if (getPri(c) > getPri(operator_s.top()))
        {
            operator_s.push(c);
        }
        else
        {
            suffix += operator_s.top();
            operator_s.pop();

            // 递归调用，比较当前符号c与下一个栈顶符号的优先性
            check(c, operator_s, suffix);
        };
    };
};

// 中缀表达式转后缀表达式
string infixToSuffix(string &infix)
{
    stack<char> operator_s; // 运算符栈
    string suffix;          // 后缀表达式

    //int num = 0;
    for (int i = 0; i < infix.size(); ++i)
    {
        if (infix[i] >= '0' && infix[i] <= '9')
        {
            suffix += infix[i];
        }
        else
        {
            check(infix[i], operator_s, suffix);
        }
    }

    // 对中缀表达式的遍历结束，将栈中元素加入后缀表达式
    while (!operator_s.empty())
    {
        suffix += operator_s.top();
        operator_s.pop();
    }

    return suffix;
};

int main()
{
    string s;
    cin >> s;
    cout << infixToSuffix(s) << endl;
    return 0;
}