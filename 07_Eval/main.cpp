#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

enum node_type
{
	NUM,
	ADD,
	SUB,
	MUL,
	DIV,
	LP,
	RP,
	RET
};

struct exp_node
{
	node_type op;
	float value;
	exp_node *op1, *op2;
};

struct raw_input
{
	node_type ch;
	float val;
};

vector<raw_input> ret;

exp_node *root;

bool is_num(char ch)
{
	if (int(ch) - int('0') < 0 || int(ch) - int('9') > 0)
		return false;
	else
		return true;
};

int split_input(string s)
{
	ret.clear();
	string tmp;
	for (auto c : s)
	{
		if (is_num(c))
		{
			tmp += c;
		}
		else
		{
			raw_input oval;
			oval.val = 0;
			if (tmp != "")
			{
				raw_input tval;
				tval.ch = NUM;
				tval.val = stoi(tmp);
				ret.push_back(tval);
				tmp = "";
			};
			switch (c)
			{
			case '+':
				oval.ch = ADD;
				break;
			case '-':
				oval.ch = SUB;
				break;
			case '*':
				oval.ch = MUL;
				break;
			case '/':
				oval.ch = DIV;
				break;
			case '(':
				oval.ch = LP;
				break;
			case ')':
				oval.ch = RP;
				break;
			default:
				break;
			};
			ret.push_back(oval);
		};
	};
	if (tmp != "")
	{
		raw_input tval;
		tval.ch = NUM;
		tval.val = stoi(tmp);
		ret.push_back(tval);
	};
	return 0;
};

exp_node *phraser(int start, int end, exp_node *r)
{
	stack<raw_input> s;
};

int main()
{
	string s;
	cout << "Testing.." << endl;
	cin >> s;
	split_input(s);
	for (auto i : ret)
	{
		cout << i.val << "[" << i.ch << "]"
			 << " ";
	}
	cout << endl;

	return 0;
}
