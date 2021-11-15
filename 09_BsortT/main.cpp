#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                 ___  ______                      \n                /\\_ \\/\\__  _\\                     \n   __     __  __\\//\\ \\/_/\\ \\/ _ __    __     __   \n /'__`\\  /\\ \\/\\ \\ \\ \\ \\ \\ \\ \\/\\`'__\\/'__`\\ /'__`\\ \n/\\ \\L\\.\\_\\ \\ \\_/ | \\_\\ \\_\\ \\ \\ \\ \\//\\  __//\\  __/ \n\\ \\__/.\\_\\\\ \\___/  /\\____\\\\ \\_\\ \\_\\\\ \\____\\ \\____\\\n \\/__/\\/_/ \\/__/   \\/____/ \\/_/\\/_/ \\/____/\\/____/\n                                                  \n                                                  \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==================================================\n! This is a program to operate an AVL Tree.\n! Input command 'add 19 7 6 4 ...' to add values to tree.\n! Input command 'lvr', 'lvr' or 'lrv' to expolre the tree.\n! Input command 'find 19 7 6 3...' to search value in the tree.\n! Use 'rm 9 7 5 3...' to remove value in tree.\n! Use 'init' to clear and init tree WITH CAUTION.\n"
#define INIT_HELP "Initialize the binary sort tree.\n"
#define VLR_HELP "Print the tree in ROOT LEFT RIGHT order.\n"
#define LVR_HELP "Print the tree in LEFT ROOT RIGHT order.\n"
#define LRV_HELP "Print the tree in LEFT RIGHT ROOT order.\n"
#define ADD_HELP "Add value to graph. Format \"add N\"\n"
#define FIND_HELP "Add edge to graph. Format \"find N\"\n"
#define REMOVE_HELP "Remove value from tree. Format \"rm N\"\n "

static CMDF_RETURN init_tree(cmdf_arglist *arglist)
{
	clear_tree(root);
	root = new avl_tree;
	cout << " [Success] Binary Sort Tree cleared and initialized." << endl;
	return CMDF_OK;
};

static CMDF_RETURN vlr(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [VLR] " << endl;
	print_tree_vlr(root);
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN lvr(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [LVR] " << endl;
	print_tree_lvr(root);
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN lrv(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [LRV] " << endl;
	print_tree_lrv(root);
	cout << endl;
	return CMDF_OK;
};

bool isNumber(const string &str)
{
	for (char const &c : str)
	{
		if (std::isdigit(c) == 0)
			return false;
	}
	return true;
}

static CMDF_RETURN add_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"add 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)
			{
				cout << " [Error] Value " << arglist->args[i] << " is alerady in tree." << endl;
			}
			else
			{
				insert_val(root, stoi(arglist->args[i]));
				cout << " [Success] Value " << arglist->args[i] << " added." << endl;
			};
		};
	};
	return CMDF_OK;
};

static CMDF_RETURN find_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"find 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)
			{
				cout << " [Success] Value " << arglist->args[i] << " is in tree." << endl;
			}
			else
			{
				cout << " [Error] Value " << arglist->args[i] << " is not in tree." << endl;
			};
		};
	};
	return CMDF_OK;
};

static CMDF_RETURN rm_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"rm 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)

			{
				remove_val(root, stoi(arglist->args[i]));
				cout << " [Success] Value " << arglist->args[i] << " is removed." << endl;
			}
			else
			{
				cout << " [Error] Value " << arglist->args[i] << " is not in tree." << endl;
			};
		};
	};
	return CMDF_OK;
};

int main()
{
	root = new avl_tree;
	cmdf_init("BST> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(init_tree, "init", INIT_HELP);
	cmdf_register_command(find_node, "find", FIND_HELP);
	cmdf_register_command(add_node, "add", ADD_HELP);
	cmdf_register_command(rm_node, "rm", REMOVE_HELP);
	cmdf_register_command(vlr, "vlr", VLR_HELP);
	cmdf_register_command(lvr, "lvr", LVR_HELP);
	cmdf_register_command(lrv, "lrv", LRV_HELP);

	cmdf_commandloop();
	return 0;
	return 0;
}
