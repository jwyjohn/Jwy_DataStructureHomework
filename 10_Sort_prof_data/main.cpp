#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include "sort.h"
using namespace std;

sort_func_result (*sort_fp[11])(int *array, int array_size, bool (*cmp)(int a, int b)) =
	{default_sort,
	 bubble_sort,
	 selection_sort,
	 insertion_sort,
	 binary_insertion_sort,
	 shell_sort,
	 quick_sort,
	 heap_sort,
	 merge_sort,
	 lsd_radix_sort,
	 msd_radix_sort};
map<string, int> sorts_name = {
	{"default", 0},
	{"bubble", 1},
	{"selection", 2},
	{"insertion", 3},
	{"binsertion", 4},
	{"shell", 5},
	{"quick", 6},
	{"heap", 7},
	{"bucket", 8},
	{"merge", 9},
	{"lsd", 10},
	{"msd", 11},
};

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	//Generate a vector with 0 to N, and then shuffle it randomly.
	vector<int> test_data = {100, 1000, 10000, 100000};
	vector<int> random_int_array;
	for (int N=1000;N<20000;N+=100)
	{
		random_int_array.clear();
		for (int i = 1; i <= N; i++)
		{
			random_int_array.push_back(N-i+4);
		};
		// random_shuffle(random_int_array.begin(), random_int_array.end());
		for (auto f : sort_fp)
		{
			test_sort_function(f, random_int_array, random_int_array.size(), less_than);
		};
	}
	return 0;
}
