#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int c[24][4] = {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 2, 1}, {0, 3, 1, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0}, {1, 0, 2, 3}, {1, 0, 3, 2}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 1, 2, 0}, {3, 1, 0, 2}, {3, 2, 1, 0}, {3, 2, 0, 1}, {3, 0, 2, 1}, {3, 0, 1, 2}};

int w, h, start, end;
int M[1000][1000];
bool visited[1000][1000];
int R[1000][1000];
int walkmaze(int x, int y, int n);
int print_R();

bool is_in_bound(int x, int y)
{
	return ((x < w) && (x > 0) && (y < h) && (y > 0));
};

int start_generate_maze()
{
	memset(M, sizeof(M), 0);
	memset(R, sizeof(R), 0);
	memset(visited, sizeof(visited), 0);
	walkmaze(1, 1, 1);
	return 0;
};

int walkmaze(int x, int y, int n)
{
	if (is_in_bound(x, y) && (!visited[x][y]))
	{
		R[x][y] = n;
		visited[x][y] = true;
		// print_R();
		// cout << endl;
		// for (int i = 0; i < 4; i++)
		// 	for (int j = 0; j < 4; j++)
		// 		visited[x + dx[i]][y + dy[j]] = true;
		int di = rand() % 24;
		for (int i = 0; i < 4; i++)
		{
			walkmaze(x + 1 * dx[c[di][i]], y + 1 * dy[c[di][i]], n + 1);
		};
	};

	return 0;
};

int print_R()
{
	for (int i = 0; i <= w; i++)
	{
		for (int j = 0; j <= h; j++)
		{
			// cout << setw(4) << setfill(' ') << R[i][j];
			if (R[i][j] != 0)
			{
				M[i * 2][j * 2] = R[i][j];
				int di = 0;
				for (int d = 0; d < 4; d++)
				{
					if (R[i - dx[d]][j - dy[d]] == R[i][j])
						di = d;
				};
				// M[i * 2 - dx[di]][j * 2 - dy[di]] = R[i][j];
			};
		};
		// cout << endl;
	};
};

int print_M()
{
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
		// cout << endl;
	};
	M[2][1] = 0;
	M[2 * w - 1][2 * h - 2] = 9;
	for (int i = 1; i <= 2 * w - 1; i++)
	{
		for (int j = 1; j <= 2 * h - 1; j++)
		{
			if (M[i][j] != 0)
			{
				cout << setw(2) << setfill(' ') << " ";
				// cout << setw(3) << setfill(' ') << M[i][j];
			}
			else
			{
				// cout << setw(3) << setfill(' ') << '#';
				cout << setw(2) << setfill(' ') << "#";
			};
		};
		cout << endl;
	};
};

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	cin >> w >> h;
	start_generate_maze();
	print_R();
	cout << endl;
	print_M();
	return 0;
}
