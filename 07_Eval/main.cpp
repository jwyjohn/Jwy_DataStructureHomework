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
	RET,
	ENDP
};

struct raw_input
{
	node_type ch;
	float val;
	string txt;
	int pos;
};

struct p_node
{
	node_type op;
	float val;
	string txt;
	vector<p_node *> child;
	p_node *parent;
};

struct expr_node
{
	node_type op;
	float val;
	string txt;
	expr_node *parent, *op1, *op2;
};

vector<raw_input> ret;

p_node *root;

bool is_num(char ch)
{
	if (int(ch) - int('0') < 0 || int(ch) - int('9') > 0)
		return false;
	else
		return true;
};

int split_input(string s)
{
	// ret.clear();
	string tmp;
	int p = 0;
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
				tval.txt = tmp;
				tval.pos = p;
				p++;
				ret.push_back(tval);
				tmp = "";
			};
			switch (c)
			{
			case '+':
				oval.ch = ADD;
				oval.txt = c;
				break;
			case '-':
				oval.ch = SUB;
				oval.txt = c;
				break;
			case '*':
				oval.ch = MUL;
				oval.txt = c;
				break;
			case '/':
				oval.ch = DIV;
				oval.txt = c;
				break;
			case '(':
				oval.ch = LP;
				oval.txt = c;
				break;
			case ')':
				oval.ch = RP;
				oval.txt = c;
				break;
			default:
				break;
			};
			oval.pos = p;
			p++;
			ret.push_back(oval);
		};
	};
	if (tmp != "")
	{
		raw_input tval;
		tval.ch = NUM;
		tval.val = stoi(tmp);
		tval.txt = tmp;
		tval.pos = p;
		p++;
		ret.push_back(tval);
	};
	return 0;
};

p_node *prase1(int l, int r)
{
	p_node *res = new p_node;
	res->op = RET;
	res->txt = "EXP";
	stack<raw_input> s;
	int level = 0;
	for (int i = l; i < r; i++)
	{
		if (ret[i].ch == LP)
		{
			s.push(ret[i]);
			level++;
		}
		else if (ret[i].ch == RP && !s.empty())
		{
			if (level == 1)
			{
				// cout << "(" << s.top().pos + 1 << "," << i << ")  " << endl;
				res->child.push_back(prase1(s.top().pos + 1, i));
				res->child.back()->parent = res;
			};
			s.pop();
			level--;
		}
		else if (level == 0)
		{
			p_node *tmp = new p_node;
			tmp->op = ret[i].ch;
			tmp->txt = ret[i].txt;
			tmp->val = ret[i].val;
			tmp->parent = res;
			res->child.push_back(tmp);
		};
	};
	return res;
};

expr_node *prase2(p_node *r)
{
	stack<p_node *> v, op;
	if (r->op == NUM)
	{
		expr_node *res;
		res->txt = r->txt;
		res->op = NUM;
		res->val = r->val;
		return res;
	}
	else
	{
		p_node *sharp = new p_node;
		sharp->op = ENDP;
		sharp->txt = "#";
		op.push(sharp);
		expr_node *res;
		int ptr = 0;
		while (ptr < r->child.size())
		{
			switch (r->child[ptr]->op)
			{
			case NUM:
				v.push(r->child[ptr]);
				ptr++;
				break;
			case RET:
				v.push(r->child[ptr]);
				ptr++;
				break;
			case MUL:
				if (op.top()->op == ADD || op.top()->op == SUB || op.top()->op == ENDP)
				{
					op.push(r->child[ptr]);
					ptr++;
				}
				else if (op.top()->op == MUL || op.top()->op == DIV)
				{
					v.push(op.top());
					op.pop();
				};
				break;
			case DIV:
				if (op.top()->op == ADD || op.top()->op == SUB || op.top()->op == ENDP)
				{
					op.push(r->child[ptr]);
					ptr++;
				}
				else if (op.top()->op == MUL || op.top()->op == DIV)
				{
					v.push(op.top());
					ptr++;
					op.pop();
				};
				break;
			case ADD:
				if (op.top()->op == ENDP)
				{
					op.push(r->child[ptr]);
					ptr++;
				}
				else
				{
					v.push(op.top());
					op.pop();
				};
				break;
			case SUB:
				if (op.top()->op == ENDP)
				{
					op.push(r->child[ptr]);
					ptr++;
				}
				else
				{
					v.push(op.top());
					op.pop();
				};
				break;
			default:
				break;
			}
		};
	};
	while (!v.empty())
	{
		cout << v.top()->txt << " ";
		v.pop();
	};
	cout << endl;
	return NULL;
};

int print_root(p_node *r, string sp)
{
	cout << sp;
	string st;
	if (r == root)
		st = "-- ";
	else if (r == r->parent->child.back())
	{
		st = "`-- ";
	}
	else
	{
		st = "|-- ";
	};
	cout << st << r->txt << endl;
	if (r == root)
	{
		for (auto i : r->child)
		{
			print_root(i, sp + "    ");
		};
	}
	else
	{
		if (r == r->parent->child.back())
			for (auto i : r->child)
			{
				print_root(i, sp + "    ");
			}
		else
			for (auto i : r->child)
			{
				print_root(i, sp + "|   ");
			};
	};

	return 0;
};

int init()
{
	string s;
	cout << "Testing.." << endl;
	cin >> s;
	ret.clear();
	// raw_input fst;
	// fst.ch = LP;
	// fst.txt = '(';
	// fst.pos = 0;
	// ret.push_back(fst);
	split_input(s);
	// fst.ch = RP;
	// fst.txt = ')';
	// fst.pos = ret.size();
	// ret.push_back(fst);
	root = prase1(0, ret.size());
	print_root(root, "");
	prase2(root);
	return 0;
};

p_node *parse1(int start, int end){};

int main()
{
	init();
	for (auto i : ret)
	{
		cout << i.pos << "[" << i.txt << "]"
			 << " ";
	}
	cout << endl;

	return 0;
}
