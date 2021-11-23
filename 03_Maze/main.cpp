#include "main_header.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                                     \n                                     \n  ___ ___      __     ____      __   \n/' __` __`\\  /'__`\\  /\\_ ,`\\  /'__`\\ \n/\\ \\/\\ \\/\\ \\/\\ \\L\\.\\_\\/_/  /_/\\  __/ \n\\ \\_\\ \\_\\ \\_\\ \\__/.\\_\\ /\\____\\ \\____\\\n \\/_/\\/_/\\/_/\\/__/\\/_/ \\/____/\\/____/\n                                     \n                                     \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n=====================================\n! This is a program to generate and solve a maze.\n! FIRST, use 'init [H] [W]', to initialize a H*W maze. (H,W >= 10)\n! Then use 'solve', to solve the maze.\n! Use 'show', to show the maze.\n"

#define INIT_HELP "Use 'init [H] [W]', to initialize a H*W maze. (H,W >= 10)"
#define SOLVE_HELP "Use 'solve', to solve the maze."
#define SHOW_HELP "Use 'show', to show the maze."

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int c[24][4] = {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 2, 1}, {0, 3, 1, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0}, {1, 0, 2, 3}, {1, 0, 3, 2}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 1, 2, 0}, {3, 1, 0, 2}, {3, 2, 1, 0}, {3, 2, 0, 1}, {3, 0, 2, 1}, {3, 0, 1, 2}};

int w, h, start, end_p;
int M[1000][1000];
bool visited[1000][1000];
int R[1000][1000];
bool S_visited[1000][1000];
bool is_solved;
bool is_init = false;
vector<vector<pair<int, int>>> SOLUTION;
int walkmaze(int x, int y, int n);
int print_R();

bool is_in_bound(int x, int y)
{
	return ((x < w) && (x > 0) && (y < h) && (y > 0));
};

bool is_in_M(int x, int y)
{
	return ((x < w * 2) && (x > 0) && (y < h * 2) && (y > 0));
};

int start_generate_maze()
{
	memset(M, 0, sizeof(M));
	memset(R, 0, sizeof(R));
	memset(visited, 0, sizeof(visited));
	memset(S_visited, 0, sizeof(S_visited));
	SOLUTION.clear();
	is_solved = false;
	walkmaze(1, 1, 1);
	for (int i = 0; i <= w; i++)
	{
		for (int j = 0; j <= h; j++)
		{
			if (R[i][j] != 0)
			{
				M[i * 2][j * 2] = R[i][j];
				int di = 0;
				for (int d = 0; d < 4; d++)
				{
					if (R[i - dx[d]][j - dy[d]] == R[i][j])
						di = d;
				};
			};
		};
	};
	for (int i = 1; i <= 2 * w; i++)
	{
		for (int j = 1; j <= 2 * h; j++)
		{
			if (M[i][j] == 0)
			{
				if ((M[i - 1][j] - M[i + 1][j] == 1) || (M[i - 1][j] - M[i + 1][j] == -1))
					M[i][j] = 9;
				if ((M[i][j - 1] - M[i][j + 1] == 1) || (M[i][j - 1] - M[i][j + 1] == -1))
					M[i][j] = 9;
			}
		};
	};
	M[2][1] = 0;
	M[2 * w - 1][2 * h - 2] = 9;
	return 0;
};

int walkmaze(int x, int y, int n)
{
	if (is_in_bound(x, y) && (!visited[x][y]))
	{
		R[x][y] = n;
		visited[x][y] = true;
		int di = rand() % 24;
		for (int i = 0; i < 4; i++)
		{
			walkmaze(x + 1 * dx[c[di][i]], y + 1 * dy[c[di][i]], n + 1);
		};
	};

	return 0;
};

int print_M()
{
	cout << "   ." << endl;
	for (int i = 1; i <= 2 * w - 1; i++)
	{
		for (int j = 1; j <= 2 * h - 1; j++)
		{
			if (M[i][j] != 0)
			{
				if (M[i][j] == -1)
					cout << setw(2) << setfill(' ') << ".";
				else
					cout << setw(2) << setfill(' ') << " ";
			}
			else
			{
				cout << setw(2) << setfill(' ') << "#";
			};
		};
		cout << endl;
	};
	return 0;
};

int Solve(int x, int y, vector<pair<int, int>> sol)
{
	if (!S_visited[x][y] && is_in_M(x, y) && M[x][y] != 0)
	{
		S_visited[x][y] = true;
		vector<pair<int, int>> tmp = sol;
		tmp.push_back({x, y});
		if (x == (2 * w - 1) && y == (2 * h - 2))
		{
			SOLUTION.push_back(tmp);
			is_solved = true;
		};
		for (int i = 0; i < 4; i++)
		{
			Solve(x + dx[i], y + dy[i], tmp);
		};
	};
	return 0;
};

int calc_solution()
{
	Solve(1, 2, {});
	for (auto i : SOLUTION)
	{
		cout << " [SOLUTION] ";
		for (auto j : i)
		{
			cout << "(" << j.first << "," << j.second << ")->";
		};
		cout << "DONE!" << endl;
	};
	for (auto i : SOLUTION[0])
	{
		M[i.first][i.second] = -1;
	};
	return 0;
};

static CMDF_RETURN init_cmd(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"init 10 10\"." << endl;
		return CMDF_OK;
	};
	if (arglist->count != 2)
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"init 10 10\"." << endl;
		return CMDF_OK;
	};
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < strlen(arglist->args[j]); i++)
			if ((int(arglist->args[j][i]) - int('0')) < 0 || (int(arglist->args[j][i]) - int('0')) > 9)
			{
				cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"init 10 10\"." << endl;
				return CMDF_OK;
			};
	int wt = stoi(arglist->args[0]);
	int ht = stoi(arglist->args[1]);
	if (wt < 10 || ht < 10)
	{
		cout << " [Error] Invaild arguments!\n [Tip] H and W should be >= 10." << endl;
		return CMDF_OK;
	};
	w = wt;
	h = ht;
	start_generate_maze();
	cout << " [DONE] Maze generated:" << endl;
	print_M();
	is_init = true;
	return CMDF_OK;
};

static CMDF_RETURN solve_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize maze first using \"init [H] [W]\"." << endl;
		return CMDF_OK;
	};
	cout << " [SOVING] ..." << endl;
	calc_solution();
	cout << " [DONE] One solution is:" << endl;
	print_M();
	return CMDF_OK;
};

static CMDF_RETURN show_cmd(cmdf_arglist *arglist)
{
	if (!is_init)
	{
		cout << " [ERROR] Need to Initialize maze first using \"init [H] [W]\"." << endl;
		return CMDF_OK;
	};
	cout << " [DONE] The current maze is:" << endl;
	print_M();
	return CMDF_OK;
};

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	cmdf_init("maze> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(init_cmd, "init", INIT_HELP);
	cmdf_register_command(solve_cmd, "solve", SOLVE_HELP);
	cmdf_register_command(show_cmd, "show", SHOW_HELP);

	cmdf_commandloop();
	return 0;
}
