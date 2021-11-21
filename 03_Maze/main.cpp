#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int c[24][4] = {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 2, 1}, {0, 3, 1, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0}, {1, 0, 2, 3}, {1, 0, 3, 2}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 1, 2, 0}, {3, 1, 0, 2}, {3, 2, 1, 0}, {3, 2, 0, 1}, {3, 0, 2, 1}, {3, 0, 1, 2}};

int w, h, start, end_p;
int M[1000][1000];
bool visited[1000][1000];
int R[1000][1000];
bool S_visited[1000][1000];
bool is_solved;
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
		cout << "[SOLUTION] ";
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

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	while (1)
	{
		cin >> w >> h;
		start_generate_maze();
		cout << endl;
		print_M();
		calc_solution();
		print_M();
	};
	return 0;
}
