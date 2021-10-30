#ifndef _SORT_H__
#define _SORT_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct sort_func_result
{
    string func_name;
    int swap_count;
};

template <class T>
int print_array(T &array)
{
    for (auto i : array)
    {
        cout << i << ' ';
    };
    cout << endl;
    return 0;
};

template <class T>
int compare_and_swap(T &a, T &b)
{
    int is_swapped = 0;
    if (a > b)
    {
        T temp = a;
        a = b;
        b = temp;
        is_swapped = 1;
    };
    return is_swapped;
};

sort_func_result bubble_sort(int *array, int array_size)
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0;
    for (int i = array_size - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            swap_count += compare_and_swap(array[j], array[j + 1]);
        };
    };
    ret.swap_count = swap_count;
    return ret;
};

sort_func_result selection_sort(int *array, int array_size)
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0;
    for (int i = 0; i < array_size; i++)
    {
        for (int j = i + 1; j < array_size; j++)
        {
            swap_count += compare_and_swap(array[i], array[j]);
        };
    };
    ret.swap_count = swap_count;
    return ret;
};

#endif