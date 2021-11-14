#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

vector<int> gen_sorted(int n)
{
    vector<int> res;
    for (int i = 1; i <= n; i++)
    {
        res.push_back(i);
    };
    return res;
};

vector<int> gen_inverted_sorted(int n)
{
    vector<int> res;
    for (int i = 1; i <= n; i++)
    {
        res.push_back(n + 1 - i);
    };
    return res;
};

vector<int> gen_random(int n)
{
    vector<int> res;
    for (int i = 1; i <= n; i++)
    {
        res.push_back(i);
    };
    random_shuffle(res.begin(), res.end());
    return res;
};

int show_vector(vector<int> v)
{
    cout << v.size() << endl;
    for (auto u : v)
    {
        cout << u << " ";
    };
    cout << endl;
    return 0;
};

int write_data(vector<int> v, string filename)
{
    ofstream out(filename);
    if (!out.is_open())
        return 1;
    out << v.size() << endl;
    for (auto u : v)
    {
        out << u << " ";
    };
    out << endl;
    out.close();
    return 0;
};

vector<int> (*fp[3])(int n) = {gen_random, gen_sorted, gen_inverted_sorted};
string pre[3]={"random_","sorted_","inverted_"};

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    vector<int> random_int_array;
    int M, N, T;
    cin >> M;
    for (int m = 1; m <= M; m++)
    {
        cin >> N >> T;
        string fn = pre[T] + to_string(N) + ".in";
        write_data(fp[T](N), fn);
    };
    return 0;
}
