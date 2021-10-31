#ifndef _SORT_H__
#define _SORT_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int GLOBAL_SWAP_CNT, GLOBAL_CMP_CNT; //Side effects introduced, TOO BAD!

struct sort_func_result
{
    string func_name;
    int swap_count, compare_count;
};

int init_counter()
{
    GLOBAL_SWAP_CNT = 0;
    GLOBAL_CMP_CNT = 0;
    return 0;
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
    GLOBAL_CMP_CNT += 1;
    return flag;
};

bool grater_than(int a, int b)
{
    bool flag = (a > b);
    GLOBAL_CMP_CNT += 1;
    return flag;
};

int compare_and_swap(int &a, int &b, bool (*cmp)(int a, int b))
{
    int is_swapped = 0;
    if (!cmp(a, b))
    {
        int temp = a;
        a = b;
        b = temp;
        is_swapped = 1;
    };
    GLOBAL_SWAP_CNT += 1;
    GLOBAL_CMP_CNT += 1;
    return is_swapped;
};

template <class T>
int force_swap(T &a, T &b)
{
    int is_swapped = 1;
    T temp = a;
    a = b;
    b = temp;
    GLOBAL_SWAP_CNT += 1;
    return is_swapped;
};

sort_func_result default_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    sort(array, array + array_size, cmp);
    ret.swap_count = -1;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result bubble_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    for (int i = array_size - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            compare_and_swap(array[j], array[j + 1], cmp);
        };
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result selection_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    for (int i = 0; i < array_size; i++)
    {
        for (int j = i + 1; j < array_size; j++)
        {
            compare_and_swap(array[i], array[j], cmp);
        };
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result insertion_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    for (int i = 0; i < array_size; i++)
    {
        int tmp = array[i];
        int pos = i;
        while (pos > 0 && cmp(tmp, array[pos - 1]))
        {
            GLOBAL_SWAP_CNT += 1;
            GLOBAL_CMP_CNT += 1;
            array[pos] = array[pos - 1];
            pos--;
        };
        array[pos] = tmp;
        GLOBAL_SWAP_CNT += 1;
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result binary_insertion_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    for (int i = 0; i < array_size; i++)
    {
        int tmp = array[i];
        int begin = 0, end = i;
        while (begin < end)
        {
            int mid = (begin + end - 1) / 2;
            if (cmp(tmp, array[mid]))
                end = mid;
            else
                begin = mid + 1;
        }
        for (int k = i - 1; k >= begin; k--)
        {
            array[k + 1] = array[k];
        }
        array[begin] = tmp;
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result shell_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    // ret.func_name = __FUNCTION__;
    init_counter();
    int gap = 1;
    while (gap < array_size / 3)
        gap = 3 * gap + 1;
    while (gap)
    {
        for (int i = gap; i < array_size; i++)
        {
            int temp = array[i];

            int pos = i;
            while (pos >= gap && cmp(temp, array[pos - gap]))
            {

                force_swap(array[pos], array[pos - gap]);

                pos -= gap;
            };
            array[pos] = temp;
        };
        gap /= 3;
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    ret.func_name = __FUNCTION__;
    return ret;
};

int inside_quick_sort(int *array, int left, int right, bool (*cmp)(int a, int b))
{
    int swap_count = 0, cmp_count = 0;
    if (left < right)
    {
        int pivot = array[left];
        int low = left, high = right;
        while (low < high)
        {
            while (!cmp(array[high], pivot) && low < high)
            {
                high--;
            };

            while (!cmp(pivot, array[low]) && low < high)
            {
                low++;
            };

            swap_count += force_swap(array[high], array[low]);
        }
        swap_count += force_swap(array[left], array[high]);
        inside_quick_sort(array, left, high - 1, cmp);
        inside_quick_sort(array, low + 1, right, cmp);
    };
    GLOBAL_SWAP_CNT += swap_count;
    return 0;
};

sort_func_result quick_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0, cmp_count = 0;
    init_counter();
    inside_quick_sort(array, 0, array_size - 1, cmp);
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result heap_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0, cmp_count = 0;
    int last_non_leaf_node = array_size / 2 - 1;
    init_counter();
    int heap[array_size];
    int heap_size = array_size;
    for (int i = 0; i < array_size; i++)
        heap[i] = array[i];
    for (int i = last_non_leaf_node; i >= 0; i--)
    {
        int current_node = i;
        int smaller_child = current_node * 2 + (cmp(heap[i * 2 + 1], heap[i * 2 + 2]) ? 1 : 2);
        if (i * 2 + 2 > array_size - 1)
            smaller_child = current_node * 2 + 1;
        while (!cmp(heap[current_node], heap[smaller_child]) && smaller_child < array_size)
        {
            force_swap(heap[current_node], heap[smaller_child]);
            current_node = smaller_child;
            smaller_child = current_node * 2 + (cmp(heap[current_node * 2 + 1], heap[current_node * 2 + 2]) ? 1 : 2);
        };
    };
    for (int i = 0; i < array_size; i++)
    {
        cout << heap[i] << ' ';
    };
    cout << endl;
    int pos = 0;
    while (heap_size > 0)
    {
        array[pos] = heap[0];
        heap[0] = heap[heap_size - 1];
        heap[heap_size - 1] = 2147483647;
        heap_size--;
        pos++;
        int current_node = 0;
        int smaller_child = current_node * 2 + (cmp(heap[current_node * 2 + 1], heap[current_node * 2 + 2]) ? 1 : 2);
        if (current_node * 2 + 2 > heap_size - 1)
            smaller_child = current_node * 2 + 1;
        while (!cmp(heap[current_node], heap[smaller_child]) && smaller_child < heap_size)
        {
            force_swap(heap[current_node], heap[smaller_child]);
            current_node = smaller_child;
            smaller_child = current_node * 2 + (cmp(heap[current_node * 2 + 1], heap[current_node * 2 + 2]) ? 1 : 2);
        };
    };

    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

sort_func_result bucket_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    init_counter();
    const int bucket_size = 1000;
    unsigned char *bucket = new unsigned char[bucket_size];
    memset(bucket, 0, sizeof(bucket));
    for (int i = 0; i < array_size; i++)
    {
        bucket[array[i]] += 1;
    };
    int pos = 0;
    for (int i = 0; i < bucket_size; i++)
    {
        while (bucket[i] > 0)
        {
            bucket[i]--;
            array[pos] = i;
            pos++;
        };
    };
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    delete[] bucket;
    return ret;
};

int inside_merge_sort(int *array, int left, int right, bool (*cmp)(int a, int b))
{
    int mid = (left + right) / 2;
    cout << "A MERGE FOX IS CALLED. " << left << ' ' << mid << ' ' << right << endl;

    if (right == left)
    {
        cout << "NOTHING TO DO. " << left << ' ' << mid << ' ' << right << endl;
        return 0;
    };

    // if (right == left + 1)
    // {
    //     compare_and_swap(array[left], array[right], cmp);
    //     GLOBAL_SWAP_CNT += 1;
    //     GLOBAL_CMP_CNT += 1;
    //     return 0;
    // };
    int swap_count = 0, cmp_count = 0;

    inside_merge_sort(array, left, mid, cmp);
    inside_merge_sort(array, mid + 1, right, cmp);

    cout << "A MERGE FOX FINISHED. " << left << ' ' << mid << ' ' << right << endl;

    vector<int> left_merged(array + left, array + mid + 1);
    vector<int> right_merged(array + mid + 1, array + right + 1);
    int pos = right;
    print_array(left_merged);
    print_array(right_merged);
    while (!left_merged.empty() && !right_merged.empty())
    {
        if (cmp(left_merged.back(), right_merged.back()))
        {
            array[pos] = right_merged.back();
            pos--;
            right_merged.pop_back();

            print_array(left_merged);
            print_array(right_merged);
        }
        else
        {
            array[pos] = left_merged.back();
            pos--;
            left_merged.pop_back();

            print_array(left_merged);
            print_array(right_merged);
        };
        swap_count++;
    };
    while (!left_merged.empty())
    {
        array[pos] = left_merged.back();
        pos--;
        left_merged.pop_back();
        swap_count++;
        print_array(left_merged);
        print_array(right_merged);
    };
    while (!right_merged.empty())
    {
        array[pos] = right_merged.back();
        pos--;
        right_merged.pop_back();
        swap_count++;
        print_array(left_merged);
        print_array(right_merged);
    };
    for (int i = left; i <= right; i++)
    {
        cout << array[i] << ' ';
    };
    cout << endl;
    GLOBAL_SWAP_CNT += swap_count;
    return 0;
};

sort_func_result merge_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
    sort_func_result ret;
    ret.func_name = __FUNCTION__;
    int swap_count = 0, cmp_count = 0;
    init_counter();
    inside_merge_sort(array, 0, array_size - 1, cmp);
    ret.swap_count = GLOBAL_SWAP_CNT;
    ret.compare_count = GLOBAL_CMP_CNT;
    return ret;
};

int test_sort_function(sort_func_result (*fp)(int *array, int array_size, bool (*cmp)(int a, int b)), const vector<int> random_int_array, const int array_size, bool (*cmp)(int a, int b))
{
    int array_to_sort[random_int_array.size()], array_after_sort[random_int_array.size()];
    sort_func_result res;
    memcpy(array_to_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
    memcpy(array_after_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
    cout << endl;
    res = fp(array_after_sort, array_size, cmp);
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
        cout << array_after_sort[i] << ' ';
    };
    cout << endl
         << endl;
    cout << "Swap calls = " << res.swap_count << endl;
    cout << "Compare calls = " << res.compare_count << endl;
    return 0;
};

#endif
