/*** Start of inlined file: sort.h ***/
#ifndef _SORT_H__
#define _SORT_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	int w = 8, num = 0;
	cout << '\t';
	for (auto i : array)
	{
		cout << i << '\t';
		num++;
		if (num % w == 0)
			cout << endl
				 << '\t';
	};
	cout << endl;
	return 0;
};

int print_array_short(vector<int> a)
{
	cout << " [Dataset] " << a[0] << " " << a[1] << " " << a[2] << " ... " << a.back() << endl;
	cout << " [Size] " << a.size() << endl;
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
	const int bucket_size = 1000000;
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
	// cout << "A MERGE FOX IS CALLED. " << left << ' ' << mid << ' ' << right << endl;

	if (right == left)
	{
		// cout << "NOTHING TO DO. " << left << ' ' << mid << ' ' << right << endl;
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

	// cout << "A MERGE FOX FINISHED. " << left << ' ' << mid << ' ' << right << endl;

	vector<int> left_merged(array + left, array + mid + 1);
	vector<int> right_merged(array + mid + 1, array + right + 1);
	int pos = right;
	// print_array(left_merged);
	// print_array(right_merged);
	while (!left_merged.empty() && !right_merged.empty())
	{
		if (cmp(left_merged.back(), right_merged.back()))
		{
			array[pos] = right_merged.back();
			pos--;
			right_merged.pop_back();

			// print_array(left_merged);
			// print_array(right_merged);
		}
		else
		{
			array[pos] = left_merged.back();
			pos--;
			left_merged.pop_back();

			// print_array(left_merged);
			// print_array(right_merged);
		};
		swap_count++;
	};
	while (!left_merged.empty())
	{
		array[pos] = left_merged.back();
		pos--;
		left_merged.pop_back();
		swap_count++;
		// print_array(left_merged);
		// print_array(right_merged);
	};
	while (!right_merged.empty())
	{
		array[pos] = right_merged.back();
		pos--;
		right_merged.pop_back();
		swap_count++;
		// print_array(left_merged);
		// print_array(right_merged);
	};
	// for (int i = left; i <= right; i++)
	// {
	//     cout << array[i] << ' ';
	// };
	// cout << endl;
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

// bool lsd_radix_sort_cmp(int a, int b, int pos, bool (*cmp)(int a, int b))
// {
//     int pos_a = (a >> pos) & 1;
//     int pos_b = (b >> pos) & 1;
//     return cmp(pos_a, pos_b);
// };

int inside_lsd_radix_sort(int *array, int array_size, bool (*cmp)(int a, int b), int pos)
{
	vector<int> num[2];
	int lsd = 0;
	for (int i = 0; i < array_size; i++)
	{
		lsd = (array[i] >> pos) & 1;
		GLOBAL_CMP_CNT++;
		num[lsd].push_back(array[i]);
	};
	num[0].insert(num[0].end(), num[1].begin(), num[1].end());
	for (int i = 0; i < array_size; i++)
	{
		array[i] = num[0][i];
		GLOBAL_SWAP_CNT++;
	};
	return 0;
};

sort_func_result lsd_radix_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
	sort_func_result ret;
	ret.func_name = __FUNCTION__;
	init_counter();
	for (int i = 0; i < 32; i++)
	{
		inside_lsd_radix_sort(array, array_size, cmp, i);
	};
	ret.swap_count = GLOBAL_SWAP_CNT;
	ret.compare_count = GLOBAL_CMP_CNT;
	return ret;
};

int inside_msd_radix_sort(int *array, int left, int right, bool (*cmp)(int a, int b), int pos)
{
	if (left == right || pos < 0)
		return 0;
	vector<int> num[2];
	int lsd = 0;
	for (int i = left; i <= right; i++)
	{
		lsd = (array[i] >> pos) & 1;
		GLOBAL_CMP_CNT++;
		num[lsd].push_back(array[i]);
	};
	int size_0 = num[0].size();
	int size_1 = num[1].size();
	// cout << '*' << size_0 << ' ' << size_1 << ' ' << right - left + 1 << ' ' << left << ' ' << left + size_0 - 1 << ' ' << left + size_0 << ' ' << right << endl;
	num[0].insert(num[0].end(), num[1].begin(), num[1].end());
	for (int i = 0; i < num[0].size(); i++)
	{
		array[left + i] = num[0][i];
		GLOBAL_SWAP_CNT++;
	};
	// print_array(num[0]);
	if (size_0 > 0)
		inside_msd_radix_sort(array, left, left + size_0 - 1, cmp, pos - 1);
	if (size_1 > 0)
		inside_msd_radix_sort(array, left + size_0, right, cmp, pos - 1);
	return 0;
};

sort_func_result msd_radix_sort(int *array, int array_size, bool (*cmp)(int a, int b))
{
	sort_func_result ret;
	ret.func_name = __FUNCTION__;
	init_counter();
	inside_msd_radix_sort(array, 0, array_size - 1, cmp, 31);
	ret.swap_count = GLOBAL_SWAP_CNT;
	ret.compare_count = GLOBAL_CMP_CNT;
	return ret;
};

int test_sort_function(sort_func_result (*fp)(int *array, int array_size, bool (*cmp)(int a, int b)), const vector<int> random_int_array, const int array_size, bool (*cmp)(int a, int b))
{
	cout << " [Preparing] Copying dataset to sort func..." << endl;
	int array_to_sort[random_int_array.size()], array_after_sort[random_int_array.size()];
	sort_func_result res;
	memcpy(array_to_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
	memcpy(array_after_sort, &random_int_array[0], random_int_array.size() * sizeof(random_int_array[0]));
	cout << " [Done] Data prepared, start to sort." << endl;
	time_point<high_resolution_clock> start, end;
	start = high_resolution_clock::now();;
	res = fp(array_after_sort, array_size, cmp);
	end = high_resolution_clock::now();;
	cout << " [" << res.func_name << "]" << endl;
	cout << " [After sorting]";
	int w = 8;
	cout << endl;
	cout << '\t' ;
	for (int i = 0; i < array_size; i++)
	{
		cout << array_after_sort[i] << '\t';
		if ((i + 1) % w == 0)
			cout << endl << '\t';
	};
	cout << endl
		 << endl;
	cout << " [Swap calls] " << res.swap_count << endl;
	cout << " [Compare calls] " << res.compare_count << endl;
	cout << " [Clocks used] " << duration_cast<microseconds>(end - start).count() << " clocks" << endl;
	return 0;
};

sort_func_result (*sort_fp[12])(int *array, int array_size, bool (*cmp)(int a, int b)) =
	{default_sort,
	 bubble_sort,
	 selection_sort,
	 insertion_sort,
	 binary_insertion_sort,
	 shell_sort,
	 quick_sort,
	 heap_sort,
	 bucket_sort,
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
#endif

/*** End of inlined file: sort.h ***/

/*** Start of inlined file: libcmdf.h ***/
#ifndef LIBCMDF_H_INCLUDE
#define LIBCMDF_H_INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#endif

/* Configuration */
#ifndef CMDF_MAX_COMMANDS
#define CMDF_MAX_COMMANDS 24
#endif

#ifndef CMDF_TAB_TO_SPACES
#define CMDF_TAB_TO_SPACES 8
#endif

/* Max sub process count */
#ifndef CMDF_MAX_SUBPROCESSES
#define CMDF_MAX_SUBPROCESSES 4
#endif

#ifdef _WIN32
#define CMDF_PPRINT_RIGHT_OFFSET 2
#else
#define CMDF_PPRINT_RIGHT_OFFSET 1
#endif

/* GNU Readline support (Unix/Linux only) */
#ifdef _WIN32
#ifdef CMDF_READLINE_SUPPORT
#undef CMDF_READLINE_SUPPORT
#endif
#else
#ifdef CMDF_READLINE_SUPPORT
#include <readline/readline.h>
#include <readline/history.h>
#endif
#endif

/* fgets()-like function to use for input handling */
#ifndef CMDF_FGETS
#define CMDF_FGETS fgets
#endif

/* malloc()-like function to use for memory allocations */
#ifndef CMDF_MALLOC
#define CMDF_MALLOC malloc
#endif

/* free()-like function to use for memory freeing */
#ifndef CMDF_FREE
#define CMDF_FREE free
#endif

/* Maximum input buffer length */
#ifndef CMDF_MAX_INPUT_BUFFER_LENGTH
#define CMDF_MAX_INPUT_BUFFER_LENGTH 256
#endif

/* STDIN and STDOUT */
#ifndef CMDF_STDIN
#define CMDF_STDIN stdin
#endif

#ifndef CMDF_STDOUT
#define CMDF_STDOUT stdout
#endif

/* =================================================================================== */

/* Error codes (for CMDF_RETURN) */
#define CMDF_OK 1
#define CMDF_ERROR_TOO_MANY_COMMANDS -1
#define CMDF_ERROR_TOO_MANY_ARGS -2
#define CMDF_ERROR_UNKNOWN_COMMAND -3
#define CMDF_ERROR_ARGUMENT_ERROR -4
#define CMDF_ERROR_OUT_OF_MEMORY -5

/* Max processes count reached */
#define CMDF_ERROR_OUT_OF_PROCESS_STACK -6

/* =================================================================================== */

/* For the C++ support */
#ifdef __cplusplus
extern "C"
{
#endif

	/* cmdf_windowsize struct */
	struct cmdf_windowsize
	{
#ifdef _WIN32
		SHORT h, w;
#else
	unsigned short h, w;
#endif
	};

	/* libcmdf command list and arglist */
	typedef struct cmdf___arglist_s
	{
		char **args;  /* NULL-terminated string list */
		size_t count; /* Argument list count */
	} cmdf_arglist;

	/* Command callback typedef */
	typedef int CMDF_RETURN;
	typedef CMDF_RETURN (*cmdf_command_callback)(cmdf_arglist *arglist);

	/* Utility Functions */
	char *cmdf__strdup(const char *src);
	void cmdf__trim(char *src);
	void cmdf__print_title(const char *title, char ruler);
	void cmdf__pprint(size_t loffset, const char *const strtoprint);
	void cmdf__print_command_list();

	/* Init/Free functions */
	void cmdf_init(const char *prompt, const char *intro, const char *doc_header,
				   const char *undoc_header, char ruler, int use_default_exit);
#define cmdf_init_quick() cmdf_init(NULL, NULL, NULL, NULL, 0, 1)
#define cmdf_quit ;

	/* Public interface functions */
	void cmdf_commandloop(void);

	/* Getters */
	const char *cmdf_get_prompt(void);
	const char *cmdf_get_intro(void);
	const char *cmdf_get_doc_header(void);
	const char *cmdf_get_undoc_header(void);
	char cmdf_get_ruler(void);
	int cmdf_get_command_count(void);

	/* Setters */
	void cmdf_set_prompt(const char *new_prompt);
	void cmdf_set_intro(const char *new_intro);
	void cmdf_set_doc_header(const char *new_doc_header);
	void cmdf_set_undoc_header(const char *new_undoc_header);

	/* Argument Parsing */
	cmdf_arglist *cmdf_parse_arguments(char *argline);
	void cmdf_free_arglist(cmdf_arglist *arglist);

	/* Adding/Removing Command Entries */
	CMDF_RETURN cmdf_register_command(cmdf_command_callback callback, const char *cmdname,
									  const char *help);

	/* Default callbacks */
	CMDF_RETURN cmdf__default_do_help(cmdf_arglist *arglist);
	CMDF_RETURN cmdf__default_do_command(const char *cmdname, cmdf_arglist *arglist);
	CMDF_RETURN cmdf__default_do_emptyline(cmdf_arglist *arglist /* Unused */);
	CMDF_RETURN cmdf__default_do_exit(cmdf_arglist *arglist /* Unused */);
	CMDF_RETURN cmdf__default_do_noop(cmdf_arglist *arglist /* Unused */);
	void cmdf__default_commandloop(void);

/* Utility Functions */
#ifdef _WIN32
	struct cmdf_windowsize cmdf_get_window_size_win(void);
#define cmdf_get_window_size cmdf_get_window_size_win
#else
struct cmdf_windowsize cmdf_get_window_size_unix(void);
#define cmdf_get_window_size cmdf_get_window_size_unix
#endif

/* ReadLine-related functions and callbackes.
 * Compiled only if readline is enabled */
#ifdef CMDF_READLINE_SUPPORT
	char **cmdf__command_name_completion(const char *text, int start, int end);
	char *cmdf__command_name_iter(const char *text, int state);
#endif

#endif /* LIBCMDF_H_INCLUDE */

	/*
 * ======================================================================================
 * IMPLEMENTATION
 * ======================================================================================
 */

	/* Defaults */
	static const char *cmdf__default_prompt = "(libcmdf) ";
	static const char *cmdf__default_intro = "";
	static const char *cmdf__default_doc_header = "Documented Commands:";
	static const char *cmdf__default_undoc_header = "Undocumented Commands:";
	static const char cmdf__default_ruler = '=';

	/* libcmdf settings */
	struct cmdf__settings_s
	{
		/* Properties */
		const char *prompt, *intro, *doc_header, *undoc_header;
		char ruler;

		/* Counters */
		int undoc_cmds, doc_cmds, entry_count;

		/* Index in cmdf__entries array from which commands would be active */
		int entry_start;

		/* Flags */
		int exit_flag;

		/* Callback pointers */
		cmdf_command_callback do_emptyline;
		CMDF_RETURN(*do_command)
		(const char *, cmdf_arglist *);
	};

	/* libcmdf settings stack */
	static struct cmdf__settings_stack_s
	{
		struct cmdf__settings_s stack[CMDF_MAX_SUBPROCESSES];
		size_t size;
		struct cmdf__settings_s *top; /* actual settings for currect process */
	} cmdf__settings_stack = {0};

	static struct cmdf__entry_s
	{
		const char *cmdname;			/* Command name */
		const char *help;				/* Help */
		cmdf_command_callback callback; /* Command callback */
	} cmdf__entries[(CMDF_MAX_COMMANDS + 1) * CMDF_MAX_SUBPROCESSES];

	/* Utility Functions */
	char *cmdf__strdup(const char *src)
	{
		char *dst = (char *)(CMDF_MALLOC(sizeof(char) * (strlen(src) + 1))); /* src + '\0' */
		if (!dst)
			return NULL;

		return strcpy(dst, src);
	}

	void cmdf__trim(char *src)
	{
		char *begin = src, *end, *newline;
		size_t end_location;

		/* Check for empty string */
		if (strlen(src) == 1 && (src[0] == '\n' || src[0] == '\0'))
		{
			src[0] = '\0';
			return;
		}

		/* Replace newline */
		newline = strrchr(src, '\n');
		if (newline)
			*newline = '\0';

		/* Replace spaces and re-align the string */
		while (isspace((int)*begin))
			begin++;

		if (src != begin)
		{
			end_location = strlen(begin);
			memmove(src, begin, strlen(begin) + 1);
			memset(begin + end_location, '\0', sizeof(char) * strlen(begin - end_location));
		}

		/* Replaces spaces at the end of the string */
		end = strrchr(src, '\0');

		/* Check if we haven't reached the end of the string.
	 * Because if we did, we have nothing else to do. */
		if (src == end)
			return;
		else
			end--;

		if (isspace((int)*end))
		{
			do
			{
				*end = '\0';
				end--;
			} while (isspace((int)*end));
		}
	}

	void cmdf__print_title(const char *title, char ruler)
	{
		size_t i = 0;

		fprintf(CMDF_STDOUT, "\n%s\n", title);

		for (i = 0; i < strlen(title) + 1; i++)
			putc(ruler, CMDF_STDOUT);

		putc('\n', CMDF_STDOUT);
	}

	/*
 * Print a string from the current line, down to the next line if needed,
 * which is padded with loffset characters.
 * The function takes the input string and prints it word by word - if a word can not
 * be printed on the line without being concatenated, it is printed on the next line.
 */
	void cmdf__pprint(size_t loffset, const char *const strtoprint)
	{
		const struct cmdf_windowsize winsize = cmdf_get_window_size();
		size_t total_printed = loffset, i, wordlen;
		char *strbuff = cmdf__strdup(strtoprint), *wordptr;

		/* If we couldn't allocate a buffer, print regularly, exit. */
		if (!strbuff)
		{
			fprintf(CMDF_STDOUT, "\n%s\n", strtoprint);
			return;
		}

		/* Begin splitting by words */
		wordptr = strtok(strbuff, " \t\n");
		while (wordptr)
		{
			/* Check if we can print this word. */
			wordlen = strlen(wordptr);
			if (total_printed + (wordlen + 1) > (size_t)(winsize.w - CMDF_PPRINT_RIGHT_OFFSET))
			{
				/* Go to the next line and print the word there. */
				/* Print newline and loffset spaces */
				fputc('\n', CMDF_STDOUT);
				for (i = 0; i < loffset; i++)
					fputc(' ', CMDF_STDOUT);

				total_printed = loffset;
			}

			/* Print the word */
			fprintf(CMDF_STDOUT, "%s ", wordptr);
			total_printed += wordlen + 1; /* strlen(word) + space */

			/* Get the next word */
			wordptr = strtok(NULL, " \t\n");
		}

		/* Put newline */
		fputc('\n', CMDF_STDOUT);

		/* Free the string */
		CMDF_FREE(strbuff);
	}

	void cmdf__print_command_list(void)
	{
		int i, printed;
		const struct cmdf_windowsize winsize = cmdf_get_window_size();

		/* Print documented commands */
		cmdf__print_title(cmdf__settings_stack.top->doc_header, cmdf__settings_stack.top->ruler);
		for (i = cmdf__settings_stack.top->entry_start, printed = 0; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
		{
			if (cmdf__entries[i].help)
			{
				/* Check if we need to break into the next line. */
				if (printed + strlen(cmdf__entries[i].cmdname) + 1 >= winsize.w)
				{
					printed = 0;
					fputc('\n', CMDF_STDOUT);
				}

				/* Print command */
				printed += fprintf(CMDF_STDOUT, "%s ", cmdf__entries[i].cmdname);
			}
		}

		/* Newline */
		fputc('\n', CMDF_STDOUT);

		/* Print undocumented commands, if any */
		if (cmdf__settings_stack.top->undoc_cmds > 0)
		{
			cmdf__print_title(cmdf__settings_stack.top->undoc_header, cmdf__settings_stack.top->ruler);
			for (i = cmdf__settings_stack.top->entry_start, printed = 0; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
			{
				if (!cmdf__entries[i].help)
				{
					/* Check if we need to break into the next line. */
					if (printed + strlen(cmdf__entries[i].cmdname) + 1 >= winsize.w)
					{
						printed = 0;
						fputc('\n', CMDF_STDOUT);
					}

					/* Print command */
					printed += fprintf(CMDF_STDOUT, "%s ", cmdf__entries[i].cmdname);
				}
			}

			/* Print newline */
			fputc('\n', CMDF_STDOUT);
		}
	}

	/* Init/Free functions */
	void cmdf_init(const char *prompt, const char *intro, const char *doc_header,
				   const char *undoc_header, char ruler, int use_default_exit)
	{
		/* Create new settings to push them to stack */
		struct cmdf__settings_s settings;
		memset((void *)&settings, 0, sizeof(struct cmdf__settings_s));
		/* Set properties */
		settings.prompt = prompt ? prompt : cmdf__default_prompt;
		settings.intro = intro ? intro : cmdf__default_intro;
		settings.doc_header = doc_header ? doc_header : cmdf__default_doc_header;
		settings.undoc_header = undoc_header ? undoc_header : cmdf__default_undoc_header;
		settings.ruler = ruler ? ruler : cmdf__default_ruler;
		settings.doc_cmds = settings.undoc_cmds = settings.entry_count = 0;

		/* If not first - look for actual entry_start index */
		if (cmdf__settings_stack.top != NULL)
			settings.entry_start = cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count;

		/* Set command callbacks */
		settings.do_command = cmdf__default_do_command;
		settings.do_emptyline = cmdf__default_do_emptyline;

		/* Push value to the stack */
		if (cmdf__settings_stack.size < CMDF_MAX_SUBPROCESSES)
		{
			cmdf__settings_stack.stack[cmdf__settings_stack.size] = settings;
			cmdf__settings_stack.top = cmdf__settings_stack.stack + cmdf__settings_stack.size;
			cmdf__settings_stack.size++;
		}
		else
		{
			printf("max subprocesses count reached!\n");
			exit(CMDF_ERROR_OUT_OF_PROCESS_STACK); /* maybe handle error somehow */
		}

		/* Register help callback */
		cmdf_register_command(cmdf__default_do_help, "help", "Get information on a command"
															 " or list commands.");

		/* Register exit callback, if required */
		if (use_default_exit)
			cmdf_register_command(cmdf__default_do_exit, "exit", "Quit the application");

#ifdef CMDF_READLINE_SUPPORT
		/* Set completion function */
		rl_attempted_completion_function = cmdf__command_name_completion;
#endif
	}

	/* Public interface functions */
	void cmdf_commandloop(void)
	{
		cmdf__default_commandloop();
	}

	/* Getters */
	const char *cmdf_get_prompt(void)
	{
		return cmdf__settings_stack.top->prompt;
	}

	const char *cmdf_get_intro(void)
	{
		return cmdf__settings_stack.top->intro;
	}

	const char *cmdf_get_doc_header(void)
	{
		return cmdf__settings_stack.top->doc_header;
	}

	const char *cmdf_get_undoc_header(void)
	{
		return cmdf__settings_stack.top->undoc_header;
	}

	char cmdf_get_ruler(void)
	{
		return cmdf__settings_stack.top->ruler;
	}

	int cmdf_get_command_count(void)
	{
		return cmdf__settings_stack.top->entry_count;
	}

	/* Setters */
	void cmdf_set_prompt(const char *new_prompt)
	{
		cmdf__settings_stack.top->prompt = new_prompt ? new_prompt : cmdf__default_prompt;
	}

	void cmdf_set_intro(const char *new_intro)
	{
		cmdf__settings_stack.top->intro = new_intro ? new_intro : cmdf__default_intro;
	}

	void cmdf_set_doc_header(const char *new_doc_header)
	{
		cmdf__settings_stack.top->doc_header = new_doc_header ? new_doc_header : cmdf__default_doc_header;
	}

	void cmdf_set_undoc_header(const char *new_undoc_header)
	{
		cmdf__settings_stack.top->undoc_header = new_undoc_header ? new_undoc_header : cmdf__default_undoc_header;
	}

	/* Argument Parsing */
	cmdf_arglist *cmdf_parse_arguments(char *argline)
	{
		cmdf_arglist *arglist = NULL;
		size_t i;
		char *strptr, *startptr;
		enum states
		{
			NONE,
			IN_WORD,
			IN_QUOTES
		} state = NONE;

		/* Check if there are any arguments */
		if (!argline)
			return NULL;

		/* Allocate argument list */
		arglist = (cmdf_arglist *)(CMDF_MALLOC(sizeof(cmdf_arglist)));
		if (!arglist)
			return NULL;

		arglist->count = 0;

		/* First pass on the arguments line - use the state machine to determine how many
	 * argument do we have. */
		for (strptr = startptr = argline, i = 0; *strptr; strptr++)
		{
			switch (state)
			{
			case NONE:
				/*
				 * Space = Don't care.
				 * Quotes = a quoted argument begins.
				 * Anything else = Inside a word.
				 */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
					state = IN_QUOTES;
				else
					state = IN_WORD;

				break;
			case IN_QUOTES:
				/*
				 * Space = Don't care, since we're inside quotes.
				 * Quotes = Quotes have ended, so count++
				 * Anything else = Don't care, since we're inside quotes.
				 */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
				{
					state = NONE;
					arglist->count++;

					break;
				}
				else
					continue;
			case IN_WORD:
				/*
				 * Space = A word just terminated, so count++
				 * Quotes = Ignore - quote is part of the word
				 * Anything else = Still in word
				 */
				if (isspace((int)*strptr))
				{
					state = NONE;
					arglist->count++;

					break;
				}
				else if (*strptr == '\"')
					continue;
				else
					continue;
			}
		}

		/* Handle last argument counting, if any */
		if (state != NONE)
			arglist->count++;

		/* Now we can allocate the argument list */
		arglist->args = (char **)(CMDF_MALLOC(sizeof(char *) * (arglist->count + 1))); /* + NULL */
		if (!arglist->args)
		{
			CMDF_FREE(arglist);
			return NULL;
		}

		/* Populate argument list */
		state = NONE;
		for (strptr = startptr = argline, i = 0; *strptr; strptr++)
		{
			switch (state)
			{
			case NONE:
				/* Space = No word yet.
				 * Quotes = Quotes started, so ignore everything inbetween.
				 * Else = Probably a word. */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
				{
					state = IN_QUOTES;
					startptr = strptr + 1;
				}
				else
				{
					state = IN_WORD;
					startptr = strptr;
				}

				break;
			case IN_QUOTES:
				/* Space = Ignore it, iterate futher.
				 * Quotes = End quotes, so put the entire quoted part as an argument.
				 * Else = Whatever is between the quotes */
				if (*strptr == '\"')
				{
					*strptr = '\0';
					arglist->args[i++] = cmdf__strdup(startptr);
					state = NONE;
				}

				break;
			case IN_WORD:
				/* Space = End of word, so parse it.
				 * Quote = Some quote inside of a word. We treat it is a word.
				 * Else = Still a word. */
				if (isspace((int)*strptr))
				{
					*strptr = '\0';
					arglist->args[i++] = cmdf__strdup(startptr);
					state = NONE;
				}

				break;
			}
		}

		/* Get the last argument, if any. */
		if (state != NONE && i < arglist->count)
			arglist->args[i++] = cmdf__strdup(startptr);

		/* Set up null terminator in the argument list */
		arglist->args[i] = NULL;

		/* Done. */
		return arglist;
	}

	void cmdf_free_arglist(cmdf_arglist *arglist)
	{
		size_t i;

		/* Check if any argument list was provided. */
		if (arglist)
		{
			/* Free every argument */
			for (i = 0; i < arglist->count - 1; i++)
				CMDF_FREE(arglist->args[i]);

			/* Free args */
			CMDF_FREE(arglist->args);
		}

		/* Free arglist */
		CMDF_FREE(arglist);
	}

	/* Adding/Removing Command Entries */
	CMDF_RETURN cmdf_register_command(cmdf_command_callback callback, const char *cmdname,
									  const char *help)
	{
		int new_index;

		/* Increate entry count, first checking if we can add more */
		if (cmdf__settings_stack.top->entry_count == CMDF_MAX_COMMANDS)
			return CMDF_ERROR_TOO_MANY_COMMANDS;

		/* Initialize new entry */
		new_index = cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count;
		cmdf__entries[new_index].callback = callback;
		cmdf__entries[new_index].cmdname = cmdname;
		cmdf__entries[new_index].help = help;

		cmdf__settings_stack.top->entry_count++;

		/* Check doc */
		if (help)
			cmdf__settings_stack.top->doc_cmds++;
		else
			cmdf__settings_stack.top->undoc_cmds++;

		return CMDF_OK;
	}

	/* Default callbacks */
	CMDF_RETURN cmdf__default_do_help(cmdf_arglist *arglist)
	{
		int i;
		size_t offset;

		/* If no arguments provided, print all help listing.
	 * Otherwise, print documentation on specified command. */
		if (arglist)
		{
			if (arglist->count == 1)
			{
				for (i = cmdf__settings_stack.top->entry_start; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
				{
					if (strcmp(arglist->args[0], cmdf__entries[i].cmdname) == 0)
					{
						/* Print help, if any */
						if (cmdf__entries[i].help)
						{
							offset = fprintf(CMDF_STDOUT, "%s   ", cmdf__entries[i].cmdname);
							cmdf__pprint(offset, cmdf__entries[i].help);
						}
						else
							printf("\n(No documentation)\n");

						return CMDF_OK;
					}
				}

				/* If we reached this, means that the command was not found */
				fprintf(CMDF_STDOUT, "Command '%s' was not found.\n", arglist->args[0]);
				return CMDF_ERROR_UNKNOWN_COMMAND;
			}
			else
			{
				fprintf(CMDF_STDOUT, "Too many arguments for the 'help' command!\n");
				return CMDF_ERROR_TOO_MANY_ARGS;
			}
		}
		else
			cmdf__print_command_list();

		/* Print newline */
		fputc('\n', CMDF_STDOUT);

		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_emptyline(cmdf_arglist *arglist /* Unusued */)
	{
		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_exit(cmdf_arglist *arglist /* Unused */)
	{
		cmdf__settings_stack.top->exit_flag = 1;

		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_noop(cmdf_arglist *arglist /* Unused */)
	{
		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_command(const char *cmdname, cmdf_arglist *arglist)
	{
		int i;

		/* Iterate through the commands list. Find and execute the appropriate command */
		for (i = cmdf__settings_stack.top->entry_start; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
			if (strcmp(cmdname, cmdf__entries[i].cmdname) == 0)
				return cmdf__entries[i].callback(arglist);

		return CMDF_ERROR_UNKNOWN_COMMAND;
	}

	void cmdf__default_commandloop(void)
	{
#ifndef CMDF_READLINE_SUPPORT
		char inputbuff[CMDF_MAX_INPUT_BUFFER_LENGTH];
#else
	char *inputbuff;
#endif

		char *cmdptr, *argsptr, *spcptr;
		cmdf_arglist *cmd_args;
		int retflag;

		/* Print intro, if any. */
		if (cmdf__settings_stack.top->intro)
			printf("\n%s\n\n", cmdf__settings_stack.top->intro);

		while (!cmdf__settings_stack.top->exit_flag)
		{
/* Print prompt and get input */
#ifndef CMDF_READLINE_SUPPORT
			fprintf(CMDF_STDOUT, "%s", cmdf__settings_stack.top->prompt);
			fgets(inputbuff, sizeof(char) * CMDF_MAX_INPUT_BUFFER_LENGTH, CMDF_STDIN);

			/* Check for EOF */
			if (feof(CMDF_STDIN))
			{
				cmdf__settings_stack.top->exit_flag = 1;
				continue;
			}
#else
		inputbuff = readline(cmdf__settings_stack.top->prompt);

		/* EOF, or failure to allocate a buffer. Means we probably need to exit. */
		if (!inputbuff)
		{
			cmdf__settings_stack.top->exit_flag = 1;
			continue;
		}
#endif

			/* Trim string */
			cmdf__trim(inputbuff);

			/* If input is empty, call do_emptyline command. */
			if (inputbuff[0] == '\0')
			{
				cmdf__settings_stack.top->do_emptyline(NULL);
				continue;
			}

			/* If we've reached this, then line has something in it.
		 * If readline is enabled, save this to history. */
#ifdef CMDF_READLINE_SUPPORT
			add_history(inputbuff);
#endif

			/* Split by first space.
		 * This should be the command, followed by arguments. */
			if ((spcptr = strchr(inputbuff, ' ')))
			{
				*spcptr = '\0';

				cmdptr = inputbuff;
				argsptr = spcptr + 1;
			}
			else
			{
				cmdptr = inputbuff;
				argsptr = NULL;
			}

			/* Parse arguments */
			cmd_args = cmdf_parse_arguments(argsptr);

			/* Execute command. */
			retflag = cmdf__settings_stack.top->do_command(cmdptr, cmd_args);
			switch (retflag)
			{
			case CMDF_ERROR_UNKNOWN_COMMAND:
				fprintf(CMDF_STDOUT, "Unknown command '%s'.\n", cmdptr);
				break;
			}

			/* Free arguments */
			cmdf_free_arglist(cmd_args);

#ifdef CMDF_READLINE_SUPPORT
			/* Free buffer */
			free(inputbuff);
#endif
		}

		/* Pop out settings from settings stack */
		cmdf__settings_stack.size--;
		cmdf__settings_stack.top--;
	}

/* Utility Functions */
#ifdef _WIN32
	struct cmdf_windowsize cmdf_get_window_size_win(void)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		struct cmdf_windowsize winsize = {0, 0};

		/* If this fails, return the zeroed structure as-is */
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) == 0)
			return winsize;

		winsize.w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		winsize.h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		return winsize;
	}
#else
struct cmdf_windowsize cmdf_get_window_size_unix(void)
{
	struct cmdf_windowsize cm_winsize;
	struct winsize ws;
	int stdin_fd = fileno(CMDF_STDIN);

	memset(&cm_winsize, 0, sizeof(struct cmdf_windowsize));

	/* if this ioctl() fails, return the zeroed struct as-is */
	if (ioctl(stdin_fd, TIOCGWINSZ, &ws) == -1)
		return cm_winsize;

	cm_winsize.w = ws.ws_col;
	cm_winsize.h = ws.ws_row;

	return cm_winsize;
}

#endif

/* readline-related utilities */
#ifdef CMDF_READLINE_SUPPORT

	char **cmdf__command_name_completion(const char *text, int start, int end)
	{
		char **matches = NULL;

		rl_attempted_completion_over = 1;
		matches = rl_completion_matches(text, cmdf__command_name_iter);

		return matches;
	}

	char *cmdf__command_name_iter(const char *text, int state)
	{
		static int list_index;
		static size_t len;
		char *name = NULL;

		if (!state)
		{
			list_index = cmdf__settings_stack.top->entry_start;
			len = strlen(text);
		}

		/* Compare all entries */
		for (; list_index < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; list_index++)
			if (strncmp(cmdf__entries[list_index].cmdname, text, len) == 0)
				name = cmdf__strdup(cmdf__entries[list_index].cmdname);

		return name;
	}

#endif

/*** End of inlined file: libcmdf.h ***/

/* For the C++ support. */
#ifdef __cplusplus
}
#endif

/*** Start of inlined file: main.cpp ***/
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <exception>

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                     __      \n                    /\\ \\__   \n  ____    ___   _ __\\ \\ ,_\\  \n /',__\\  / __`\\/\\`'__\\ \\ \\/  \n/\\__, `\\/\\ \\L\\ \\ \\ \\/ \\ \\ \\_ \n\\/\\____/\\ \\____/\\ \\_\\  \\ \\__\\\n \\/___/  \\/___/  \\/_/   \\/__/\n                             \n                             \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n=============================\n! This is a program to compare sort algorithms.\n! Input command 'prep 10000 rand' to generate dataset.\n! Input command 'show' to inspect dataset.\n! If you want to see all the available algorithms , use 'help test'.\n! Use 'test bubble' to run bubble sort on the dataset.\n"
#define SHOW_HELP "Used to inspect full dataset.\n"
#define SEED_HELP "Used to inspect the random seed.\n"
#define TEST_HELP "Used to run sort algorithm.\n Available algorithms can be found using \"test help\""
#define PREP_HELP "Used to prepare dataset.\n Enter the command like \"prepare_dataset N rand/seq/inv\", where N is a number and rand/seq/inv indicates the sequence of data.\n"

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
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please Enter the command like \"prep 200 rand/seq/inv\"" << endl;
		return CMDF_OK;
	}
	if (!check_prepare_dataset(arglist))
	{
		cout << " [Sytax Error] Invaild arguments!\n [Tip] Please Enter the command like \"prep 200 rand/seq/inv\"" << endl;
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
		cout << " [Data Error] Dataset not generated or too small.\n [Tip] Please generate the dataset using \"prep 100 rand/seq/inv\"" << endl;
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
		cout << " [Tip] Vaild sort algorithms are:" << endl;
		for (auto u : sorts_name)
		{
			cout << "\t- " << u.first << endl;
		};
		return CMDF_OK;
	};
	if (strcmp(arglist->args[0], "help") == 0)
	{
		cout << " [Tip] Vaild sort algorithms are:" << endl;
		for (auto u : sorts_name)
		{
			cout << "\t- " << u.first << endl;
		};
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
	cmdf_register_command(show_dataset, "show", SHOW_HELP);
	cmdf_register_command(show_seed, "seed", SEED_HELP);
	cmdf_register_command(prepare_dataset, "prep", PREP_HELP);
	cmdf_register_command(test_sort, "test", TEST_HELP);

	cmdf_commandloop();
	return 0;
}

/*** End of inlined file: main.cpp ***/

