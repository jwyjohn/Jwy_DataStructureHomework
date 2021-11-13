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

#define PROG_INTRO "                                       \n                                       \n   __   __  __     __     __    ___    \n /'__`\\/\\ \\/\\ \\  /'__`\\ /'__`\\/' _ `\\  \n/\\ \\L\\ \\ \\ \\_\\ \\/\\  __//\\  __//\\ \\/\\ \\ \n\\ \\___, \\ \\____/\\ \\____\\ \\____\\ \\_\\ \\_\\\n \\/___/\\ \\/___/  \\/____/\\/____/\\/_/\\/_/\n      \\ \\_\\                            \n       \\/_/                            \n\n - Free Software by 1951510 Jiang Wenyuan \nNov 2021\n=======================================\n! This is a program to solve the n-queen problem.\n! Input command 'solve 8 n' to calculate the solutions in the n=8 case.\n! If you want to see all the solution chess board in detail, use 'solve 8 n'.\n! You can change 8 to any int (< than 32) to get more general solutions.\n"

#define SOLVE_HELP "Use like 'solve 8 y' or 'solve 9 n'. If you want to show all chessboards, use y, else use n."

static CMDF_RETURN solve_queen(cmdf_arglist *arglist)
{
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
		cout << " [Size Error] Too large chessborad size!\n [Tip] Try between 4 to 32" << endl;
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
