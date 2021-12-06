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



















#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include <fstream>
#include <sstream>

#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO " __  __           ____    \n/\\ \\/\\ \\  /'\\_/`\\/\\  _`\\  \n\\ \\ \\/'/'/\\      \\ \\ \\L\\ \\\n \\ \\ , < \\ \\ \\__\\ \\ \\ ,__/\n  \\ \\ \\\\`\\\\ \\ \\_/\\ \\ \\ \\/ \n   \\ \\_\\ \\_\\ \\_\\\\ \\_\\ \\_\\ \n    \\/_/\\/_/\\/_/ \\/_/\\/_/ \n                          \n                          \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==========================\n! This is a program to find substring in a file.\n! Can also create, read, append a file.\n! Input command 'c mytext.txt' to create mytext.txt.\n! Input command 'r mytext.txt' to read from mytext.txt.\n! Input command 'a mytext.txt' to append content to mytext.txt.\n! Input command 's' to show loaded text.\n! Input command 'f substr' to serach substr in loaded text.\n! Use 'c mytext.txt' WITH CAUTION because it can overwrite existing file.\n"
#define NEW_HELP "Create a new file and enter text into it. Format 'c mytext.txt'\n"
#define FIND_HELP "Find a substring in the loaded file. Format 'f substr'\n"
#define CAT_HELP "Show loaded file.\n"
#define READ_HELP "Read text from a file. Format 'r mytext.txt'\n"
#define APPEND_HELP "Append text to a file. Format 'a mytext.txt'\n"
using namespace std;

// 一些全局变量，用于暂存读入或要写入的文件

string filename;
string contents;

static CMDF_RETURN read_filename(cmdf_arglist *arglist)
{
	/**
	 * @brief 处理用户输入，读文件
	 * 
	 */

	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"r mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"r mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	FILE *fp = fopen(arglist->args[0], "r");
	char ch;
	if (fp == NULL)
	{
		cout << " [Error] Unable to open file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Loaded file: " << filename << endl;
	};
	while ((ch = fgetc(fp)) != EOF)
	{
		contents += ch;
	};
	fclose(fp);
	return CMDF_OK;
};

static CMDF_RETURN show_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 显示文件暂存区内容
	 * 
	 */
	cout << " [" << filename << "] :" << endl;
	cout << contents << endl;
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN create_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 由用户输入创建文件
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	FILE *fp = fopen(arglist->args[0], "w");
	char ch;
	if (fp == NULL)
	{
		cout << " [Error] Unable to create file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Created file: " << filename << endl;
		cout << " [Tip] Input your file here (Crtl+D to end)" << endl;
	};
	contents.clear();
	while ((ch = getchar()) != EOF)
	{
		fputc(ch, fp);
		contents += ch;
	};
	fclose(fp);
	clearerr(CMDF_STDIN);
	return CMDF_OK;
};

static CMDF_RETURN append_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 对现有文件进行追加
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	contents.clear();
	FILE *fp1 = fopen(arglist->args[0], "r");
	char ch;
	if (fp1 == NULL)
	{
		cout << " [Error] Unable to open file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Loaded file: " << filename << endl;
	};
	while ((ch = fgetc(fp1)) != EOF)
	{
		contents += ch;
	};
	fclose(fp1);
	ch = 0;
	FILE *fp2 = fopen(arglist->args[0], "a");
	if (fp2 == NULL)
	{
		cout << " [Error] Unable to append file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Tip] Input your text to append here (Crtl+D to end)" << endl;
	};
	while ((ch = getchar()) != EOF)
	{
		fputc(ch, fp2);
		contents += ch;
	};
	fclose(fp2);
	clearerr(CMDF_STDIN);
	return CMDF_OK;
};

static CMDF_RETURN find_str(cmdf_arglist *arglist)
{
	/**
	 * @brief 查找字符串功能
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"f somestr\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"f somestr\"" << endl;
		return CMDF_OK;
	};
	if (contents == "")
	{
		cout << " [Error] No contents in memory. Please read, write or append a file." << endl;
		return CMDF_OK;
	};
	kmp_text tmp(contents);
	pair<int, vector<int>> res = tmp.countWord(arglist->args[0]);
	cout << " [Number of substr] " << res.first << endl;
	cout << " [Pos of substr] ";
	for (auto u : res.second)
	{
		cout << u << ", ";
	};
	cout << endl;
	return CMDF_OK;
};

int main()
{
	cmdf_init("keyword> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(read_filename, "r", READ_HELP);
	cmdf_register_command(show_file, "s", CAT_HELP);
	cmdf_register_command(create_file, "c", NEW_HELP);
	cmdf_register_command(append_file, "a", APPEND_HELP);
	cmdf_register_command(find_str, "f", FIND_HELP);

	cmdf_commandloop();
	return 0;
}
