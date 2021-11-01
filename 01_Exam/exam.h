#ifndef _EXAM_H__
#define _EXAM_H__

#define MAX_CHESSBOARD_SIZE 32
#define MAX_STACK_SIZE 10000
#define _QUEEN 7

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

struct exam_candidate
{
    /* data */
    int No = 0;
    string name = "";
    int Gender = 0;
    int Age = 0;
    string subject = "";
    exam_candidate *next = NULL;
    exam_candidate *pre = NULL;
};

struct op_parms
{
    // int op_code = 0;
    int no = 0;
    exam_candidate *candidate = NULL;
};

exam_candidate head;

int init_link();
int clear_link();
exam_candidate *find_candidate(int no);
int insert_candidate_after(int no, exam_candidate *candidate);
int remove_candidate(int no);
int show_candidates();
int show_single_candidate(exam_candidate *candidate);
exam_candidate *find_candidate(op_parms parms);
int insert_candidate_after(op_parms parms);
int remove_candidate(op_parms parms);
int show_candidates(op_parms parms);
int show_single_candidate(op_parms parms);

map<string, int> op_list = {{"ls", 0}, {"find", 1}, {"add", 2}, {"rm", 3}};
map<string, int> parm_list = {{"ls", 0}, {"find", 16}, {"add", 63}, {"rm", 16}}; // pos32 no16 name8 gender4 age2 subject1
const int parm_is_string = 13;
int (*func_ptr[4])(op_parms parms) = {show_candidates, show_single_candidate, insert_candidate_after, remove_candidate};
// Thank 644617926 for debugging.
int process_input(string op)
{
    int parm_needed = (parm_list.find(op) != parm_list.end()) ? parm_list[op] : -1;
    if (parm_needed == -1)
    {
        cout << "Unknown command." << endl;
        return 1;
    };
    string user_input[6];
    int tmp[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 5; i >= 0; i--)
    {
        int res = (parm_needed >> i) & 1;
        int is_string = (parm_is_string >> i) & 1;
        // cout << res << ' ';
        if (res == 1)
        {
            cin >> user_input[i];
            if (is_string != 1)
                tmp[i] = stoi(user_input[i]);
        };
    };
    exam_candidate *candidate_to_add = new exam_candidate;
    candidate_to_add->No = tmp[4];
    candidate_to_add->Age = tmp[1];
    candidate_to_add->Gender = tmp[2];
    candidate_to_add->name = user_input[3];
    candidate_to_add->subject = user_input[0];
    int pos = tmp[5];
    show_single_candidate(candidate_to_add);
    cout << endl;
    op_parms parms;
    parms.candidate = candidate_to_add;
    parms.no = pos;
    int func_needed = (op_list.find(op) != op_list.end()) ? op_list[op] : -1;
    int ret_code;
    ret_code = func_ptr[func_needed](parms);
    return ret_code;
};

int show_single_candidate(exam_candidate *candidate)
{
    if (candidate == NULL)
        return 1;
    cout << "  No." << candidate->No
         << "  Name: " << candidate->name
         << "  Gender: " << candidate->Gender
         << "  Age: " << candidate->Age
         << "  Subject: " << candidate->subject << endl;
    return 0;
};

int init_link()
{
    return 0;
};

int clear_link()
{
    return 0;
};

exam_candidate *find_candidate(op_parms parms)
{
    return find_candidate(parms.no);
};

int insert_candidate_after(op_parms parms)
{
    return insert_candidate_after(parms.no, parms.candidate);
};

int remove_candidate(op_parms parms)
{
    return remove_candidate(parms.candidate->No);
};

int show_candidates(op_parms parms)
{
    return show_candidates();
};

int show_single_candidate(op_parms parms)
{
    return show_single_candidate(parms.candidate);
};

exam_candidate *find_candidate(int no)
{
    exam_candidate *ptr = &head;
    if (no == 0)
        return ptr;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        if (ptr->No == no)
            return ptr;
    };
    return NULL;
};

int insert_candidate_after(int no, exam_candidate *candidate)
{
    exam_candidate *insert_position = find_candidate(no);
    if (insert_position == NULL)
        return 1;
    if (insert_position->next != NULL)
    {
        exam_candidate *tmp = insert_position->next;
        insert_position->next = candidate;
        candidate->pre = insert_position;
        candidate->next = tmp;
        tmp->pre = candidate;
    }
    else
    {
        insert_position->next = candidate;
        candidate->pre = insert_position;
    };
    return 0;
};

int remove_candidate(int no)
{
    exam_candidate *remove_position = find_candidate(no);
    if (remove_position == NULL)
        return 1;
    if (remove_position->next != NULL)
    {
        // exam_candidate *tmp = remove_position;
        remove_position->pre->next = remove_position->next;
        remove_position->next->pre = remove_position->pre;
        delete remove_position;
    }
    else
    {
        remove_position->pre->next = NULL;
        delete remove_position;
    };
    return 0;
};

int show_candidates()
{
    exam_candidate *ptr = head.next;
    while (ptr != NULL)
    {
        cout << ptr->No << ' ' << ptr->name << endl;
        ptr = ptr->next;
    }
    return 0;
};



#endif
