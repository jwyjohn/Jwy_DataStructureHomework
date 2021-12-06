/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 具体函数的实现
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <string>
#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO "                                    __         \n __                                /\\ \\        \n/\\_\\    ___     ____     __   _____\\ \\ \\___    \n\\/\\ \\  / __`\\  /',__\\  /'__`\\/\\ '__`\\ \\  _ `\\  \n \\ \\ \\/\\ \\L\\ \\/\\__, `\\/\\  __/\\ \\ \\L\\ \\ \\ \\ \\ \\ \n _\\ \\ \\ \\____/\\/\\____/\\ \\____\\\\ \\ ,__/\\ \\_\\ \\_\\\n/\\ \\_\\ \\/___/  \\/___/  \\/____/ \\ \\ \\/  \\/_/\\/_/\n\\ \\____/                        \\ \\_\\          \n \\/___/                          \\/_/          \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n===============================================\n! This is a program to simulate the Joseph problem.\n! Use 'solve [N] [S] [M] [K]', to solve a Joseph case with N participants,\n!  start from position S, kill every M position, and have K survivors. \n! (note: N>K>0, N>=S>=1 and M>0)\n"

#define SOLVE_HELP "Use 'solve [N] [S] [M] [K]', to solve a Joseph case with N participants, start from position S, kill every M position, and have K survivors. (note: N>K>0, N>=S>=1 and M>0)"

using namespace std;

struct node
{
	/**
	 * @brief 循环链表的节点
	 * 
	 */
	int no;
	node *next;
};

/**
 * @brief 两个指针，pre为current前一个元素，以方便删除元素。
 * 
 */
node *current;
node *pre;

int N, S, M, K;

int init()
{
	/**
	 * @brief 初始化循环链表
	 * 
	 */
	current = new node;
	node *first = current;
	for (int i = 1; i < N; i++)
	{
		current->no = i;
		current->next = new node;
		current = current->next;
		// cout << i << endl;
	};
	current->no = N;
	current->next = first;
	pre = current;
	while (pre->next->no != S)
	{
		pre = pre->next;
	};
	current = pre->next;
	return 0;
};

static CMDF_RETURN solve_joseph(cmdf_arglist *arglist)
{
	/**
	 * @brief 处理用户输入
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"solve 30 1 9 15\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 4)
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"solve 30 1 9 15\"" << endl;
		return CMDF_OK;
	};
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < strlen(arglist->args[j]); i++)
			if ((int(arglist->args[j][i]) - int('0')) < 0 || (int(arglist->args[j][i]) - int('0')) > 9)
			{
				cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"test 8 y/n\"" << endl;
				return CMDF_OK;
			};
	N = stoi(arglist->args[0]);
	S = stoi(arglist->args[1]);
	M = stoi(arglist->args[2]);
	K = stoi(arglist->args[3]);
	if (N <= 0)
	{
		cout << " [Error] Invaild arguments!\n [Tip] N should be > 0." << endl;
		return CMDF_OK;
	};
	if (M <= 0)
	{
		cout << " [Error] Invaild arguments!\n [Tip] M should be > 0." << endl;
		return CMDF_OK;
	};
	if (S <= 0 || S > N)
	{
		cout << " [Error] Invaild arguments!\n [Tip] S should be N>=S>=1." << endl;
		return CMDF_OK;
	};
	if (K <= 0 || K >= N)
	{
		cout << " [Error] Invaild arguments!\n [Tip] K should be N>K>0." << endl;
		return CMDF_OK;
	};
	init();
	solve();
	return CMDF_OK;
};

int solve()
{
	/**
	 * @brief 模拟问题求解过程
	 * 
	 */
	int count = N;
	int j = 1;
	string ch = "th";
	while (count > K)
	{
		for (int i = 0; i < M - 1; i++)
		{
			current = current->next;
			pre = pre->next;
		};
		/**
		 * @brief 用户友好的输出
		 * 
		 */
		if (j % 10 == 1 && j != 11)
			ch = "st";
		else if (j % 10 == 2 && j != 12)
			ch = "nd";
		else if (j % 10 == 3 && j != 13)
			ch = "rd";
		else
			ch = "th";
		cout << "[KILLED] The position of the " << j << ch << " dead man is: " << current->no << endl;
		j++;
		pre->next = current->next;
		delete current;
		current = pre->next;
		count--;
		/**
		 * @brief 经典的循环链表操作
		 * 
		 */
	};
	cout << endl;
	if (K != 1)
	{
		cout << "The " << K << " survivors are: ";
	}
	else
	{
		cout << "The only survivor is: ";
	};
	node *stop = current;
	while (current->next != stop)
	{
		cout << current->no << " ";
		current = current->next;
	};
	cout << current->no << " ";
	cout << endl;
	// node *to_del;
	// while (current->next != NULL)
	// {
	// 	to_del = current;
	// 	current = current->next;
	// 	delete to_del;
	// };
	return 0;
};

int main()
{
	cmdf_init("joseph> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(solve_joseph, "solve", SOLVE_HELP);

	cmdf_commandloop();
	return 0;
}
