/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 函数的具体实现和主程序
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */



















#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO "   ___                     ___                    \n /'___\\                   /\\_ \\    __             \n/\\ \\__/   __      ___ ___ \\//\\ \\  /\\_\\  __  __    \n\\ \\ ,__\\/'__`\\  /' __` __`\\ \\ \\ \\ \\/\\ \\/\\ \\/\\ \\   \n \\ \\ \\_/\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\ \\_\\ \\_\\ \\ \\ \\ \\_\\ \\  \n  \\ \\_\\\\ \\__/.\\_\\ \\_\\ \\_\\ \\_\\/\\____\\\\ \\_\\/`____ \\ \n   \\/_/ \\/__/\\/_/\\/_/\\/_/\\/_/\\/____/ \\/_/`/___/> \\\n                                            /\\___/\n                                            \\/__/ \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==================================================\n! This is a program to manage a family tree.\n! FIRST, use 'init [Name]', to initialize a tree with root name [Name]\n! Then use 'add [Parent] [Child]', to add a child to a parent.\n! Use 'show', to show the family tree.\n! Use 'del', to delete a member and its children.\n! Use 'rename [Old] [New]', to rename a member.\n"

#define INIT_HELP "Use 'init [Name]', to initialize a tree with root name [Name]"
#define ADD_HELP "Use 'add [Child] [Parent]', to add a child to a parent."
#define SHOW_HELP "Use 'show', to show the family tree."
#define DEL_HELP "Use 'del', to delete a member and its children."
#define RENAME_HELP "Use 'rename [Old] [New]', to rename a member."

bool is_init = false;

struct family_node
{
	/**
	 * @brief 家庭成员节点的结构体
	 * 
	 */
	string name;
	vector<family_node *> children;
	family_node *parent;
} root;

int init(string root_name)
{
	/**
	 * @brief 初始化根节点
	 * 
	 */
	root.name = root_name;
	root.parent = &root;
	root.children.clear();
	return 0;
};

class F
{
private:
	bool is_init = false;
	family_node root;
	int init(string root_name)
	{
		root.name = root_name;
		root.parent = &root;
		root.children.clear();
		return 0;
	};
	family_node *find_family_i(family_node *r, string name)
	{
		/**
		 * @brief 树里查找节点
		 * 
		 */
		if (r->name == name)
			return r;
		family_node *ret = NULL;
		for (auto f : r->children)
		{
			ret = find_family_i(f, name);
			if (ret != NULL)
				return ret;
		};
		return NULL;
	};
	int del_family_i(family_node *to_del)
	{
		/**
		 * @brief 删除节点
		 * 
		 */
		if (to_del != NULL)
		{
			for (auto i : to_del->children)
			{
				del_family_i(i);
			};
			delete to_del;
		};
		return 0;
	};
	int print_family_i(family_node *r, string sp)
	{
		/**
		 * @brief 递归打印家谱树
		 * 
		 */
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
				print_family_i(i, sp + "    ");
			};
		}
		else
		{
			if (r == r->parent->children.back())
				for (auto i : r->children)
				{
					print_family_i(i, sp + "    ");
				}
			else
				for (auto i : r->children)
				{
					print_family_i(i, sp + "|   ");
				};
		};

		return 0;
	};

public:
/**
 * @brief 常用的增查删改的接口
 * 
 * @return int 
 */
	int print_family() { return print_family_i(&root, ""); };
	int add_family(string rname, string name)
	{
		family_node *ins = find_family_i(&root, rname);
		if (ins != NULL)
		{
			family_node *to_ins = new family_node;
			to_ins->name = name;
			to_ins->parent = ins;
			ins->children.push_back(to_ins);
			cout << " [DONE] Added " << name << " to " << rname << "." << endl;
		}
		else
		{
			cout << " [ERROR] family " << rname << " not found" << endl;
		};
		return 0;
	};
	int remove_family(string rname)
	{
		family_node *to_del = find_family_i(&root, rname);
		if (to_del == &root)
		{
			cout << " [ERROR] Cannot delete root." << endl;
			return 0;
		};
		if (to_del != NULL)
		{
			string tmp = to_del->name;
			vector<family_node *>::iterator iter = std::remove(to_del->parent->children.begin(), to_del->parent->children.end(), to_del);
			to_del->parent->children.erase(iter, to_del->parent->children.end());
			del_family_i(to_del);
			cout << " [DONE] Deleted " << tmp << "." << endl;
		}
		else
		{
			cout << " [ERROR] family " << rname << " not found" << endl;
		};
		return 0;
	};
	int rename_family(string rname, string name)
	{
		family_node *ins = find_family_i(&root, rname);
		if (ins != NULL)
		{
			ins->name = name;
			cout << " [DONE] Renamed " << rname << " to " << name << "." << endl;
		}
		else
		{
			cout << " [ERROR] family " << rname << " not found" << endl;
		};
		return 0;
	};
};

/**
 * @brief 具体的函数实现
 * 
 */

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
		cout << " [DONE] Added " << name << " to " << rname << "." << endl;
	}
	else
	{
		cout << " [ERROR] family " << rname << " not found" << endl;
	};
	return 0;
};

int rename_family(string rname, string name)
{
	family_node *ins = find_family(&root, rname);
	if (ins != NULL)
	{
		ins->name = name;
		cout << " [DONE] Renamed " << rname << " to " << name << "." << endl;
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
	if (to_del == &root)
	{
		cout << " [ERROR] Cannot delete root." << endl;
		return 0;
	};
	if (to_del != NULL)
	{
		string tmp = to_del->name;
		vector<family_node *>::iterator iter = std::remove(to_del->parent->children.begin(), to_del->parent->children.end(), to_del);
		to_del->parent->children.erase(iter, to_del->parent->children.end());
		del_family(to_del);
		cout << " [DONE] Deleted " << tmp << "." << endl;
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

/**
 * @brief 处理用户输入
 * 
 * @param arglist 
 * @return CMDF_RETURN 
 */

static CMDF_RETURN init_cmd(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"init John\"." << endl;
		return CMDF_OK;
	};
	string root_name;
	// for (int i = 0; i < arglist->count; i++)
	// {
	// 	root_name += arglist->args[i];
	// };
	root.name = arglist->args[0];
	cout << " [DONE] Initialized family tree with root: " << root.name << endl;
	is_init = true;
	return CMDF_OK;
};

static CMDF_RETURN show_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize family tree first using \"init [NAME]\"." << endl;
		return CMDF_OK;
	};
	print_family(&root, "");
	return CMDF_OK;
};

static CMDF_RETURN add_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize family tree first using \"init [NAME]\"." << endl;
		return CMDF_OK;
	};
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"add [Children] [Parent] \"." << endl;
		return CMDF_OK;
	};
	if (arglist->count != 2)
	{
		cout << " [Sytax Error] Invaild number of arguments provided!\n [Tip] Please Enter the command like \"add [Children] [Parent] \"." << endl;
		return CMDF_OK;
	};
	string n1, n2;
	n1 = arglist->args[1];
	n2 = arglist->args[0];
	add_family(n1, n2);
	// cout << " [DONE] Added " << n1 << " to " << n2 << "." << endl;
	return CMDF_OK;
};

static CMDF_RETURN del_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize maze first using \"init [NAME]\"." << endl;
		return CMDF_OK;
	};
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"del [Children]\"." << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"del [Children]\"." << endl;
		return CMDF_OK;
	};
	string n1;
	n1 = arglist->args[0];
	remove_family(n1);
	return CMDF_OK;
};

static CMDF_RETURN rename_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize family tree first using \"init [NAME]\"." << endl;
		return CMDF_OK;
	};
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"rename [Before] [After] \"." << endl;
		return CMDF_OK;
	};
	if (arglist->count != 2)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"rename [Before] [After] \"." << endl;
		return CMDF_OK;
	};
	string n1, n2;
	n1 = arglist->args[0];
	n2 = arglist->args[1];
	rename_family(n1, n2);
	// cout << " [DONE] Added " << n1 << " to " << n2 << "." << endl;
	return CMDF_OK;
};

int main()
{

	cmdf_init("family> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(init_cmd, "init", INIT_HELP);
	cmdf_register_command(add_cmd, "add", ADD_HELP);
	cmdf_register_command(show_cmd, "show", SHOW_HELP);
	cmdf_register_command(rename_cmd, "rename", RENAME_HELP);
	cmdf_register_command(del_cmd, "del", DEL_HELP);

	cmdf_commandloop();
	return 0;
}
