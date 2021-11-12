#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <exception>
#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "test - A simple test program for libcmdf.\n" \
				   "You can use this as a reference on how to use the library!"
#define PRINTARGS_HELP "This is a very long help string for a command.\n" \
					   "As you can see, this is concatenated properly. It's pretty good!"

vector<int> random_int_array;
unsigned int seed = static_cast<unsigned int>(time(0));

bool check_prepare_dataset(cmdf_arglist *arglist)
{
	if (arglist->count != 2)
	{
		return false;
	};
	// cout<<"count ok"<<endl;
	for (int i = 0; i < strlen(arglist->args[0]); i++)
		if ((int(arglist->args[0][i]) - int('0')) < 0 || (int(arglist->args[0][i]) - int('0')) > 9)
			return false;
	// cout<<"number ok"<<endl;
	if (!(strcmp(arglist->args[1], "rand") == 0 || strcmp(arglist->args[1], "seq") == 0 || strcmp(arglist->args[1], "inv") == 0))
		return false;
	// cout<<"type ok"<<endl;
	return true;
};

static CMDF_RETURN prepare_dataset(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"prepare_dataset 200 rand/seq/inv\"" << endl;
		return CMDF_OK;
	}
	if (!check_prepare_dataset(arglist))
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"prepare_dataset 200 rand/seq/inv\"" << endl;
		return CMDF_OK;
	}
	int n = stoi(arglist->args[0]);
	if (n < 10)
	{
		cout << " [Data Error] Dataset size too small.\n [Tip] Try bigger N value." << endl;
		return CMDF_OK;
	};
	if (strcmp(arglist->args[1], "rand") == 0)
	{
		random_int_array.clear();
		for (int i = 1; i <= n; i++)
		{
			random_int_array.push_back(i);
		};
		random_shuffle(random_int_array.begin(), random_int_array.end());
	}
	else if (strcmp(arglist->args[1], "seq") == 0)
	{
		random_int_array.clear();
		for (int i = 1; i <= n; i++)
		{
			random_int_array.push_back(i);
		};
	}
	else if (strcmp(arglist->args[1], "inv") == 0)
	{
		random_int_array.clear();
		for (int i = 1; i <= n; i++)
		{
			random_int_array.push_back(n - i + 1);
		};
	};
	cout << " [Success] Dataset created." << endl;
	print_array_short(random_int_array);
	return CMDF_OK;
};

static CMDF_RETURN show_dataset(cmdf_arglist *arglist)
{
	cout << "[Dataset] " << endl;
	print_array(random_int_array);
	return CMDF_OK;
}

static CMDF_RETURN show_seed(cmdf_arglist *arglist)
{
	cout << "[Seed] " << seed << endl;
	return CMDF_OK;
}

static CMDF_RETURN test_sort(cmdf_arglist *arglist)
{
	if (random_int_array.size() < 10)
	{
		cout << " [Data Error] Dataset not generated or too small.\n [Tip] Please generate the dataset using \"prepare_dataset 100 rand/seq/inv\"" << endl;
		return CMDF_OK;
	};
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"test quick\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"test quick\"" << endl;
		return CMDF_OK;
	};
	if (sorts_name.find(arglist->args[0]) == sorts_name.end())
	{
		cout << " [Sytax Error] Invaild sort algorithm.\n [Tip] Vaild sort algorithms are:" << endl;
		for (auto u : sorts_name)
		{
			cout << "\t- " << u.first << endl;
		};
		return CMDF_OK;
	};
	test_sort_function(sort_fp[sorts_name[arglist->args[0]]], random_int_array, random_int_array.size(), less_than);
	cout << " [Success] Sorted." << endl;
	return CMDF_OK;
};

int main()
{
	srand(seed);
	// cout << "Testing.." << endl;
	// int N;
	// cin >> N;
	// srand(static_cast<unsigned int>(time(0)));
	// //Generate a vector with 0 to N, and then shuffle it randomly.
	// vector<int> random_int_array;
	// for (int i = 1; i <= N; i++)
	// {
	// 	random_int_array.push_back(i);
	// };
	// random_shuffle(random_int_array.begin(), random_int_array.end());
	// //print_array(random_int_array);
	// //Copy the vector to an array, which will be sorted later.
	// test_sort_function(default_sort, random_int_array, N, less_than);
	// test_sort_function(bubble_sort, random_int_array, N, less_than);
	// test_sort_function(selection_sort, random_int_array, N, less_than);
	// test_sort_function(insertion_sort, random_int_array, N, less_than);
	// test_sort_function(binary_insertion_sort, random_int_array, N, less_than);

	// test_sort_function(shell_sort, random_int_array, N, less_than);

	// test_sort_function(quick_sort, random_int_array, N, less_than);
	// test_sort_function(heap_sort, random_int_array, N, less_than);
	// test_sort_function(bucket_sort, random_int_array, N, less_than);
	// test_sort_function(merge_sort, random_int_array, N, less_than);
	// test_sort_function(lsd_radix_sort, random_int_array, N, less_than);
	// test_sort_function(msd_radix_sort, random_int_array, N, less_than);

	cmdf_init("sort> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(show_dataset, "show", NULL);
	cmdf_register_command(show_seed, "seed", NULL);
	cmdf_register_command(prepare_dataset, "prep", PRINTARGS_HELP);
	cmdf_register_command(test_sort, "test", PRINTARGS_HELP);

	cmdf_commandloop();
	return 0;
}
