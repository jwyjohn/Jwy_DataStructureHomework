#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include "sort.h"
using namespace std;

int main()
{
	int N;
	cin >> N;
	int array_to_sort[N];
	sort_func_result res;
	sort_func_result (*fp)(int *array, int array_size, bool (*cmp)(int a, int b)) = SED_HERE;
	for (int i = 0; i < N; i++)
	{
		cin >> array_to_sort[i];
	};
	res = fp(array_to_sort, N, less_than);
	cout << "Compare calls = " << res.compare_count << endl;
	return 0;
}
