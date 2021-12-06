/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 用户输入的处理和主程序
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */



















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

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO "              __                               __         \n             /\\ \\__                           /\\ \\        \n  ___      __\\ \\ ,_\\  __  __  __    ___   _ __\\ \\ \\/'\\    \n/' _ `\\  /'__`\\ \\ \\/ /\\ \\/\\ \\/\\ \\  / __`\\/\\`'__\\ \\ , <    \n/\\ \\/\\ \\/\\  __/\\ \\ \\_\\ \\ \\_/ \\_/ \\/\\ \\L\\ \\ \\ \\/ \\ \\ \\\\`\\  \n\\ \\_\\ \\_\\ \\____\\\\ \\__\\\\ \\___x___/'\\ \\____/\\ \\_\\  \\ \\_\\ \\_\\\n \\/_/\\/_/\\/____/ \\/__/ \\/__//__/   \\/___/  \\/_/   \\/_/\\/_/\n                                                          \n                                                          \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==========================================================\n! This is a program to optimize a plan for electric network.\n! Input command 'adv A B C ..' to add a city named A,B,C...\n! Input command 'ade A B 100' to add connect A WITH B at 100 million cost.\n! Input command 'show' to inspect the graph.\n! Use 'run A' to run optimization strating from city A.\n! Use 'init' to clear graph WITH CAUTION.\n"
#define INIT_HELP "Clear graph data.\n"
#define SHOW_GRAPH_HELP "Print the graph in a certain format.\n"
#define ADDE_HELP "Add node to graph. Format \"adv name1 name2 ... nameN\"\n"
#define ADDV_HELP "Add edge to graph. Format \"ade start end length\"\n"
#define RUNP_HELP "Run prim on the graph on a chosen node. Format \"run a\"\n "

enetwork elec;

/**
 * @brief 处理用户输入，下同
 * 
 * @param arglist 
 * @return CMDF_RETURN 
 */
static CMDF_RETURN init_graph(cmdf_arglist *arglist)
{
	elec.init_map();
	cout << " [Success] Graph cleared and initialized." << endl;
	return CMDF_OK;
};

static CMDF_RETURN show_graph(cmdf_arglist *arglist)
{
	// cout << " [Graph] " << endl;
	elec.print_edges();
	return CMDF_OK;
};

static CMDF_RETURN add_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"adv a b c d\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		int flag = elec.add_node(arglist->args[i]);
		if (flag == 1)
		{
			cout << " [Success] Node " << arglist->args[i] << " added." << endl;
		}
		else
		{
			cout << " [Error] Node " << arglist->args[i] << " is alerady in graph." << endl;
		};
	};
	elec.print_edges();
	return CMDF_OK;
};

bool check_add_edge(cmdf_arglist *arglist)
{
	if (arglist->count != 3)
	{
		return false;
	};

	for (int i = 0; i < strlen(arglist->args[2]); i++)
	{

		if ((int(arglist->args[2][i]) - int('0')) < 0 || (int(arglist->args[2][i]) - int('0')) > 9)
			return false;
		// cout << arglist->args[2][i] << endl;
	};
	return true;
};

static CMDF_RETURN add_edge(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"ade a b 7\"" << endl;
		return CMDF_OK;
	};
	if (!check_add_edge(arglist))
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"ade a b 7\"" << endl;
		return CMDF_OK;
	};
	if (!elec.has_node(arglist->args[0]))
	{
		cout << " [Error] Node " << arglist->args[0] << " is not in graph."
			 << endl;
		return CMDF_OK;
	};
	if (!elec.has_node(arglist->args[1]))
	{
		cout << " [Error] Node " << arglist->args[1] << " is not in graph."
			 << endl;
		return CMDF_OK;
	};
	int flag = elec.add_edge(arglist->args[0], arglist->args[1], stoi(arglist->args[2]));
	if (flag == 1)
	{
		cout << " [Success] Edge added." << endl;
		elec.print_edges();
	}
	else
	{
		cout << " [Error] Unknown Error." << endl;
		elec.print_edges();
	};
	return CMDF_OK;
};

static CMDF_RETURN run_prim(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"run a\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"run a\"" << endl;
		return CMDF_OK;
	};
	if (!elec.has_node(arglist->args[0]))
	{
		cout << " [Error] Node " << arglist->args[0] << " is not in graph.\n"
			 << endl;
		return CMDF_OK;
	};
	if (!elec.is_connected())
	{
		cout << " [Error] Graph is not connected.\n"
			 << endl;
		return CMDF_OK;
	};
	elec.run_prim(arglist->args[0]);
	return CMDF_OK;
};

int main()
{
	cmdf_init("network> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(init_graph, "init", INIT_HELP);
	cmdf_register_command(show_graph, "show", SHOW_GRAPH_HELP);
	cmdf_register_command(add_edge, "ade", ADDE_HELP);
	cmdf_register_command(add_node, "adv", ADDV_HELP);
	cmdf_register_command(run_prim, "run", RUNP_HELP);

	cmdf_commandloop();
	return 0;
}
