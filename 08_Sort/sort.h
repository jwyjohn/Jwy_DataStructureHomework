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

bool less_than(int a, int b)
{
    bool flag = (a < b);
    return flag;
};

int compare_and_swap(int &a, int &b, bool (*cmp)(int a, int b))
{
    int is_swapped = 0;
    if (cmp(a, b))
    {
        int temp = a;
        a = b;
        b = temp;
        is_swapped = 1;
    };
    return is_swapped;
};

template <class T>
int force_swap(T &a, T &b)
{
    int is_swapped = 1;
    T temp = a;
    a = b;
    b = temp;
    return is_swapped;
};

sort_func_result bubble_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0;
    for (int i = array_size - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            swap_count += compare_and_swap(array[j], array[j + 1], cmp);
        };
    };
    ret.swap_count = swap_count;
    return ret;
};

sort_func_result selection_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0;
    for (int i = 0; i < array_size; i++)
    {
        for (int j = i + 1; j < array_size; j++)
        {
            swap_count += compare_and_swap(array[i], array[j], cmp);
        };
    };
    ret.swap_count = swap_count;
    return ret;
};

int test_sort_function(sort_func_result (*fp)(int *array, int array_size, bool (*cmp)(int a, int b)), const vector<int> random_int_array, const int array_size, bool (*cmp)(int a, int b))
{
    int array_to_sort[random_int_array.size()], array_after_sort[random_int_array.size()];
    sort_func_result res;
    memcpy(array_to_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
    memcpy(array_after_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));

    cout << endl;
    res = fp(array_to_sort, array_size, cmp);
    cout << "====================" << res.func_name << "====================" << endl;
    cout << "Before sorting: ";
    for (int i = 0; i < array_size; i++)
    {
        cout << array_to_sort[i] << ' ';
    };
    cout << endl;
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

#endif