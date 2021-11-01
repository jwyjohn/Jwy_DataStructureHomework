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
    int op_code = 0;
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

int init_link()
{
    return 0;
};

int clear_link()
{
    return 0;
};

exam_candidate *find_candidate(op_parms parms);
int insert_candidate_after(op_parms parms);
int remove_candidate(op_parms parms);
int show_candidates(op_parms parms);

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
    return remove_candidate(parms.no);
};

int show_candidates(op_parms parms)
{
    return show_candidates();
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
