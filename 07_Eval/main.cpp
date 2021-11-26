#include "main_header.h"
#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <vector>
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                        ___      \n                       /\\_ \\     \n   __   __  __     __  \\//\\ \\    \n /'__`\\/\\ \\/\\ \\  /'__`\\  \\ \\ \\   \n/\\  __/\\ \\ \\_/ |/\\ \\L\\.\\_ \\_\\ \\_ \n\\ \\____\\\\ \\___/ \\ \\__/.\\_\\/\\____\\\n \\/____/ \\/__/   \\/__/\\/_/\\/____/\n                                 \n                                 \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n=================================\n! This is a program to eval an expression.\n! Use \"calc [expression]\" to caculate an expression with [0-9]+_*/().\n"

#define SOLVE_HELP "Use \"calc [expression]\" to caculate an expression with '[0-9]+_*/()'."

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
	double val;
	string txt;
	int pos;
};

struct p_node
{
	node_type op;
	double val;
	string txt;
	vector<p_node *> child;
	p_node *parent;
};

struct expr_node
{
	node_type op;
	double val;
	string txt;
	expr_node *parent = NULL, *op1 = NULL, *op2 = NULL;
	bool is_evaled = false;
};

bool is_num(char ch)
{
	if (int(ch) - int('0') < 0 || int(ch) - int('9') > 0)
		return false;
	else
		return true;
};

bool is_valid_str(string s)
{
	string allowed = "0123456789+-*/()";
	for (auto ch : s)
	{
		if (allowed.find(ch) == allowed.npos)
			return false;
	};
	return true;
};

class E
{
private:
	vector<raw_input> ret;
	p_node *root;
	expr_node *expr_root;
	bool is_error = false;
	int split_input(string s)
	{
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
		stack<p_node *> v, op, s;
		p_node *sharp = new p_node;
		sharp->op = ENDP;
		sharp->txt = "#";
		op.push(sharp);
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
			};
		};
		while (!op.empty())
		{
			v.push(op.top());
			op.pop();
		};
		while (!v.empty())
		{
			if (v.top()->op != ENDP)
				s.push(v.top());
			v.pop();
		};
		expr_node *res, *tmp;
		stack<expr_node *> exprs;
		while (!s.empty())
		{
			tmp = new expr_node;
			tmp->op = s.top()->op;
			tmp->txt = s.top()->txt;
			tmp->val = s.top()->val;
			if (s.top()->op != RET)
			{
				cout << s.top()->txt << " ";
				exprs.push(tmp);
				s.pop();
			}
			else
			{
				cout << "(";
				exprs.push(prase2(s.top()));
				cout << ") ";
				s.pop();
			};
			if ((exprs.top()->op == ADD || exprs.top()->op == SUB || exprs.top()->op == MUL || exprs.top()->op == DIV))
			{
				res = new expr_node;
				res = exprs.top();
				if (exprs.top()->op2 == NULL)
				{
					exprs.pop();
					if (exprs.empty())
					{
						is_error = true;
						cout << " ![SYTAX ERROR]" << endl;
						return NULL;
					};
					res->op2 = exprs.top();
					exprs.top()->parent = res;
					exprs.pop();
					exprs.push(res);
				};
				if (exprs.top()->op1 == NULL)
				{
					exprs.pop();
					if (exprs.empty())
					{
						is_error = true;
						cout << " ![SYTAX ERROR]" << endl;
						return NULL;
					};
					res->op1 = exprs.top();
					exprs.top()->parent = res;
					exprs.pop();
					exprs.push(res);
				};
			};
		};
		return exprs.top();
	};

	int print_r_expr(expr_node *r, string sp)
	{
		if (r == NULL)
		{
			return 0;
		};
		string st;
		if (r == expr_root)
			st = "-- ";
		else if (r == r->parent->op2)
		{
			st = "`-- ";
		}
		else
		{
			st = "|-- ";
		};
		cout << sp << st << r->txt << endl;
		if (r->op == NUM)
		{
			return 0;
		};
		if (r == expr_root)
		{
			print_r_expr(r->op1, sp + "    ");
			print_r_expr(r->op2, sp + "    ");
		}
		else if (r == r->parent->op1)
		{
			print_r_expr(r->op1, sp + "|   ");
			print_r_expr(r->op2, sp + "|   ");
		}
		else if (r == r->parent->op2)
		{
			print_r_expr(r->op1, sp + "    ");
			print_r_expr(r->op2, sp + "    ");
		};
		return 0;
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

	double eval(expr_node *r)
	{
		if (r->is_evaled)
		{
			return r->val;
		}
		else if (r->op == NUM)
		{
			r->is_evaled = true;
			// r->val = stoi(r->txt);
			return r->val;
		}
		else
		{
			double tmp;
			switch (r->op)
			{
			case ADD:
				tmp = (eval(r->op1) + eval(r->op2));
				r->is_evaled = true;
				break;
			case SUB:
				tmp = (eval(r->op1) - eval(r->op2));
				r->is_evaled = true;
				break;
			case MUL:
				tmp = (eval(r->op1) * eval(r->op2));
				r->is_evaled = true;
				break;
			case DIV:
				if (eval(r->op2) == 0)
				{
					cout << " ![DIVIDED BY ZERO]" << endl;
				};
				tmp = (eval(r->op1) / eval(r->op2));
				r->is_evaled = true;
				break;
			default:
				break;
			};
			r->val = tmp;
			return r->val;
		};
	};

	int print_midfix(expr_node *r)
	{
		if (r == NULL)
		{
			return 0;
		}
		else
		{
			if (r->op == NUM)
			{
				print_midfix(r->op1);
				cout << r->txt << " ";
				print_midfix(r->op2);
			}
			else
			{
				cout << "( ";
				print_midfix(r->op1);
				cout << r->txt << " ";
				print_midfix(r->op2);
				cout << ") ";
			};
		};
		return 0;
	};

	int print_prefix(expr_node *r)
	{
		if (r == NULL)
		{
			return 0;
		}
		else
		{
			if (r->op == NUM)
			{
				cout << r->txt << " ";
				print_prefix(r->op1);
				print_prefix(r->op2);
			}
			else
			{
				cout << "( ";
				cout << r->txt << " ";
				print_prefix(r->op1);
				print_prefix(r->op2);
				cout << ") ";
			};
		};
		return 0;
	};

	int print_sufix(expr_node *r)
	{
		if (r == NULL)
		{
			return 0;
		}
		else
		{
			print_sufix(r->op1);
			print_sufix(r->op2);
			cout << r->txt << " ";
		};
		return 0;
	};

public:
	E(string s)
	{
		is_error = false;
		ret.clear();
		if (!is_valid_str(s))
		{
			cout << " [ERROR1] Invalid expression, please recheck." << endl;
			return;
		};
		cout << " [INPUT] " << s << endl;
		split_input(s);
		if (is_error)
		{
			cout << " [ERROR2] Invalid expression, please recheck." << endl;
			return;
		};
		root = prase1(0, ret.size());
		if (is_error)
		{
			cout << " [ERROR3] Invalid expression, please recheck." << endl;
			return;
		};
		cout << " [PRASING] " << endl;
		print_root(root, "");
		expr_root = prase2(root);
		cout << endl;
		if (is_error)
		{
			cout << " [ERROR4] Invalid expression, please recheck." << endl;
			return;
		};
		cout << " [EXPR TREE] " << endl;
		print_r_expr(expr_root, "");
		cout << " [ANS] " << eval(expr_root) << endl;
		cout << " [Mid-fix Expr] ";
		print_midfix(expr_root);
		cout << endl;
		cout << " [Pre-fix Expr] ";
		print_prefix(expr_root);
		cout << endl;
		cout << " [Post-fix Expr] ";
		print_sufix(expr_root);
		cout << endl;
		return;
	};
};

static CMDF_RETURN calc_cmd(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"calc [expression]\"." << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Invaild number of arguments provided!\n [Tip] Please Enter the command like \"calc [expression]\"." << endl;
		return CMDF_OK;
	};
	string e = arglist->args[0];
	E tmpexp(e);
	return CMDF_OK;
};

int main()
{
	cmdf_init("eval> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(calc_cmd, "calc", SOLVE_HELP);

	cmdf_commandloop();

	return 0;
}
