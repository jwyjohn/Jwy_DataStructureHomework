#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include "sort.h"
using namespace std;

int test_sort_function(sort_func_result (*fp)(int *array, int array_size), const vector<int> random_int_array, const int array_size);

int main()
{
	cout << "Testing.." << endl;
	int N;
	cin >> N;

	//Generate a vector with 0 to N, and then shuffle it randomly.
	vector<int> random_int_array;
	for (int i = 1; i <= N; i++)
	{
		random_int_array.push_back(i);
	};
	random_shuffle(random_int_array.begin(), random_int_array.end());
	//print_array(random_int_array);
	//Copy the vector to an array, which will be sorted later.

	test_sort_function(bubble_sort, random_int_array, N);
	test_sort_function(selection_sort, random_int_array, N);

	return 0;
}

int test_sort_function(sort_func_result (*fp)(int *array, int array_size), const vector<int> random_int_array, const int array_size)
{
	int array_to_sort[random_int_array.size()], array_after_sort[random_int_array.size()];
	sort_func_result res;
	memcpy(array_to_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
	memcpy(array_after_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));

	cout << endl;
	res = fp(array_to_sort, array_size);
	cout<<"===================="<<res.func_name<<"===================="<<endl;
	cout << "Before sorting: ";
	for (int i = 0; i < array_size; i++)
	{
		cout << array_to_sort[i] << ' ';
	};
	cout<<endl;
	cout << "After sorting: ";
	for (int i = 0; i < array_size; i++)
	{
		cout << array_to_sort[i] << ' ';
	};
	cout << endl
		 << endl;
	cout << "Swap calls = " << res.swap_count << endl;
	return 0;
};
