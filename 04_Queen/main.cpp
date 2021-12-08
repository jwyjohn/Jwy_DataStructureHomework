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

#define PROG_INTRO "                                       \n                                       \n   __   __  __     __     __    ___    \n /'__`\\/\\ \\/\\ \\  /'__`\\ /'__`\\/' _ `\\  \n/\\ \\L\\ \\ \\ \\_\\ \\/\\  __//\\  __//\\ \\/\\ \\ \n\\ \\___, \\ \\____/\\ \\____\\ \\____\\ \\_\\ \\_\\\n \\/___/\\ \\/___/  \\/____/\\/____/\\/_/\\/_/\n      \\ \\_\\                            \n       \\/_/                            \n\n - Free Software by 1951510 Jiang Wenyuan \nNov 2021\n=======================================\n! This is a program to solve the n-queen problem.\n! Input command 'solve 8 n' to calculate the solutions in the n=8 case.\n! If you want to see all the solution chess board in detail, use 'solve 8 n'.\n! You can change 8 to any int (< than 32) to get more general solutions.\n"

#define SOLVE_HELP "Use like 'solve 8 y' or 'solve 9 n'. If you want to show all chessboards, use y, else use n."

int N = 8; //Side effects.

struct chessboard
{
	/**
	 * @brief 棋盘状态的结构体
	 * 
	 */
	int current_queen_num = 0;
	int board[MAX_CHESSBOARD_SIZE][MAX_CHESSBOARD_SIZE];
};

struct queen_stack
{
	/**
	 * @brief 放棋盘状态的栈及其实现
	 * 
	 */
	int ptr = 0;
	chessboard data[MAX_STACK_SIZE];
	queen_stack() : ptr(0){};
	bool is_empty() { return (ptr == 0); };
	bool empty() { return (ptr == 0); };
	bool is_full() { return (ptr > (MAX_STACK_SIZE - 2)); }
	chessboard top() { return data[ptr]; };
	int pop()
	{
		if (!is_empty())
		{
			ptr--;
			return 0;
		}
		else
		{
			return 1;
		};
	};
	int push(chessboard data_to_push)
	{
		if (!is_full())
		{
			ptr++;
			data[ptr] = data_to_push;

			return 0;
		}
		else
		{
			return 1;
		};
	};
	int size()
	{
		return ptr;
	};
	int clear()
	{
		ptr = 0;
		return 0;
	};
} s, ans;

int show_chessboard(chessboard board_to_show)
{
	/**
	 * @brief 打印棋盘的函数
	 * 
	 */
	char ch;
	cout << '\t';
	for (int i = 1; i < N + 1; i++)
	{

		for (int j = 1; j < N + 1; j++)
		{
			ch = (board_to_show.board[i][j] == _QUEEN) ? 'X' : 'O';
			cout << ' ' << ch;
		};
		cout << endl
			 << '\t';
	};
	cout << endl;
	return 0;
};

bool is_queen_safe(chessboard a, int x, int y)
{
	/**
	 * @brief 判断在x，y位置新增一个皇后是否安全
	 * 
	 */
	if (x > N || y > N)
		return false;
	// chessboard t = a;
	// t.board[x][y] = _QUEEN;
	bool flag = true;
	// show_chessboard(a);
	// for (int row = 0; row < N; row++)
	// {
	//     if (row != x)
	//         flag = flag && !(t.board[row][y] == _QUEEN);
	// };
	// for (int col = 0; col < N; col++)
	// {
	//     if (col != y)
	//         flag = flag && !(t.board[x][col] == _QUEEN);
	// };
	int Dx[8] = {+1, -1, 0, 0, +1, -1, +1, -1};
	int Dy[8] = {0, 0, +1, -1, +1, +1, -1, -1};
	for (int k = 0; k < 8; k++)
	{
		int dx = Dx[k], dy = Dy[k];
		int i = x, j = y;
		while (0 <= i && i <= N && j >= 0 && j <= N)
		{
			flag = flag && !a.board[i][j];
			i = i + dx, j = j + dy;
		};
	};
	return flag;
};

int queen_solution(int n, bool show_board)
{
	/**
	 * @brief 使用栈进行回溯，寻找所有可能的解
	 * 
	 */
	chessboard a;
	memset(a.board,0,sizeof(a.board));
	// stack<chessboard> s, ans;
	N = n;
	s.clear();
	ans.clear();
	s.push(a);
	while (!s.empty())
	{
		// 回溯主循环
		chessboard tmp = s.top();
		s.pop();
		tmp.current_queen_num++;
		int i = tmp.current_queen_num;
		for (int j = 1; j < N + 1; j++)
		{
			if (is_queen_safe(tmp, i, j))
			{
				tmp.board[i][j] = _QUEEN;
				if (i < N + 1)
				{
					s.push(tmp);
				}
				if (i == N)
				{
					ans.push(tmp);
				};
				tmp.board[i][j] = 0;
			};
		};
	};
	int solution_num = ans.size();
	cout << " [Success] Solved, total solution number is " << solution_num << "." << endl;
	// cout << " [Show detailed chessboards? (Y/N)] ";
	if (show_board)
	{
		int num = 1;
		while (!ans.empty())
		{
			cout << " [Solution #" << num << "]" << endl;
			num++;
			show_chessboard(ans.top());
			ans.pop();
		};
	};

	return 0;
}

static CMDF_RETURN solve_queen(cmdf_arglist *arglist)
{
	/**
	 * @brief 处理用户输入
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"solve 8 y/n\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 2)
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"test 8 y/n\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < strlen(arglist->args[0]); i++)
		if ((int(arglist->args[0][i]) - int('0')) < 0 || (int(arglist->args[0][i]) - int('0')) > 9)
		{
			cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"test 8 y/n\"" << endl;
			return CMDF_OK;
		};
	int n = stoi(arglist->args[0]);
	if (!(strcmp(arglist->args[1], "y") == 0 || strcmp(arglist->args[1], "n") == 0))
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"test 8 y/n\"" << endl;
		return CMDF_OK;
	};
	bool show_board = (strcmp(arglist->args[1], "y") == 0) ? true : false;
	if (n > MAX_CHESSBOARD_SIZE)
	{
		cout << " [Size Error] Too large chessborad size!\n [Tip] Try between 4 to 25" << endl;
		return CMDF_OK;
	};
	queen_solution(n, show_board);
	return CMDF_OK;
};

int main()
{
	cmdf_init("queen> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(solve_queen, "solve", SOLVE_HELP);

	cmdf_commandloop();
	return 0;
}
