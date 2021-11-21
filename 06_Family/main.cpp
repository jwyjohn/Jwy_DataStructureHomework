// #include "main_header.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct family_node
{
	string name;
	vector<family_node *> children;
	family_node *parent;
} root;

int init(string root_name)
{
	root.name = root_name;
	root.parent = &root;
	root.children.clear();
	return 0;
};

family_node *find_family(family_node *r, string name)
{
	if (r->name == name)
		return r;
	family_node *ret = NULL;
	for (auto f : r->children)
	{
		ret = find_family(f, name);
		if (ret != NULL)
			return ret;
	};
	return NULL;
};

int add_family(string rname, string name)
{
	family_node *ins = find_family(&root, rname);
	if (ins != NULL)
	{
		family_node *to_ins = new family_node;
		to_ins->name = name;
		to_ins->parent = ins;
		ins->children.push_back(to_ins);
	}
	else
	{
		cout << " [ERROR] family " << rname << " not found" << endl;
	};
	return 0;
};

int del_family(family_node *to_del)
{
	if (to_del != NULL)
	{
		for (auto i : to_del->children)
		{
			del_family(i);
		};
		delete to_del;
	};
	return 0;
};

int remove_family(string rname)
{
	family_node *to_del = find_family(&root, rname);
	if (to_del != NULL)
	{
		vector<family_node *>::iterator iter = std::remove(to_del->parent->children.begin(), to_del->parent->children.end(), to_del);
		to_del->parent->children.erase(iter, to_del->parent->children.end());
		del_family(to_del);
	}
	else
	{
		cout << " [ERROR] family " << rname << " not found" << endl;
	};
	return 0;
};

int print_family(family_node *r, string sp)
{
	cout << sp;
	string st;
	if (r == &root)
		st = "--- ";
	else if (r == r->parent->children.back())
	{
		st = "`-- ";
	}
	else
	{
		st = "|-- ";
	};
	cout << st << r->name << endl;
	if (r == &root)
	{
		for (auto i : r->children)
		{
			print_family(i, sp + "    ");
		};
	}
	else
	{
		if (r == r->parent->children.back())
			for (auto i : r->children)
			{
				print_family(i, sp + "    ");
			}
		else
			for (auto i : r->children)
			{
				print_family(i, sp + "|   ");
			};
	};

	return 0;
};

int main()
{
	string nr;
	cin >> nr;
	init(nr);
	int op;
	string n1, n2;
	while (1)
	{
		cin >> op;
		switch (op)
		{
		case 1:
			print_family(&root, "");
			break;
		case 2:
			cin >> n1 >> n2;
			add_family(n1, n2);
			break;
		case 3:
			cin >> n1;
			remove_family(n1);
			break;
		};
	};

	return 0;
}
