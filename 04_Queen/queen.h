#ifndef _QUEEN_H__
#define _QUEEN_H__

#define MAX_CHESSBOARD_SIZE 32
#define MAX_STACK_SIZE 10000
#define _QUEEN 7

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N = 8; //Side effects.

struct chessboard
{
    int current_queen_num = 0;
    int board[MAX_CHESSBOARD_SIZE][MAX_CHESSBOARD_SIZE];
    // chessboard()
    // {
    //     memset(board, 0, sizeof(board));
    // };
};

struct queen_stack
{
    int ptr = 0;
    chessboard data[MAX_STACK_SIZE];
    // queen_stack() : ptr(0){};
    bool is_empty() { return (ptr == 0); };
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
};

int show_chessboard(chessboard board_to_show)
{
    cout << endl;
    char ch;
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            ch = (board_to_show.board[i][j] == _QUEEN) ? 'X' : 'O';
            cout << ' ' << ch;
        };
        cout << endl;
    };
    return 0;
};

bool is_queen_safe(chessboard a, int x, int y)
{
    if (x > N || y > N)
        return false;
    // chessboard t = a;
    // t.board[x][y] = _QUEEN;
    bool flag = true;
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

#endif
