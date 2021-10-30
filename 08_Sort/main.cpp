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
	cout << "Testing.." << endl;
	int N;
	cin >> N;
	srand(static_cast<unsigned int>(time(0)));
	//Generate a vector with 0 to N, and then shuffle it randomly.
	vector<int> random_int_array;
	for (int i = 1; i <= N; i++)
	{
		random_int_array.push_back(i);
	};
	random_shuffle(random_int_array.begin(), random_int_array.end());
	//print_array(random_int_array);
	//Copy the vector to an array, which will be sorted later.
	test_sort_function(default_sort, random_int_array, N, less_than);
	test_sort_function(bubble_sort, random_int_array, N, less_than);
	test_sort_function(selection_sort, random_int_array, N, less_than);
	test_sort_function(insertion_sort, random_int_array, N, less_than);
	test_sort_function(binary_insertion_sort, random_int_array, N, less_than);

	test_sort_function(shell_sort, random_int_array, N, less_than);

	// test_sort_function(bubble_sort, random_int_array, N, grater_than);

	test_sort_function(quick_sort, random_int_array, N, less_than);
	test_sort_function(heap_sort, random_int_array, N, less_than);

	return 0;
}
