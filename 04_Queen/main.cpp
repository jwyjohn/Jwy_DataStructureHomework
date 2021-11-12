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

#define PROG_INTRO "test - A simple test program for libcmdf.\n" \
				   "You can use this as a reference on how to use the library!"
#define PRINTARGS_HELP "This is a very long help string for a command.\n" \
					   "As you can see, this is concatenated properly. It's pretty good!"

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
	cmdf_register_command(solve_queen, "solve", NULL);

	cmdf_commandloop();
	return 0;
}
