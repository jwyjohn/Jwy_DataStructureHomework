#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include "queen.h"
using namespace std;

int main()
{
	cout << "Please the chess board size N : ";
	cin >> N;
	if (N >= MAX_CHESSBOARD_SIZE)
	{
		cout << "Too Large Chessboard! " << endl;
		return 1;
	};

	chessboard a;
	stack<chessboard> s, ans;
	s.push(a);
	while (!s.empty())
	{
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
	cout << endl
		 << "The total solution is : " << solution_num << endl;
	while (!ans.empty())
	{
		show_chessboard(ans.top());
		ans.pop();
	};
	cout << endl
		 << "The total solution is : " << solution_num << endl;
	return 0;
}
