#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include "exam.h"
using namespace std;

int (*fp)(op_parms parms);

int main()
{
	cout << "Op N : ";
	int op, no, ret_code;
	string candidate_name;
	cin >> op;
	int i = 0;
	while (op != -1)
	{
		exam_candidate *candidate_to_add = new exam_candidate;
		switch (op)
		{
		case 1:
			cin >> i >>no >> candidate_name;
			candidate_to_add->No = no;
			candidate_to_add->name = candidate_name;
			ret_code = insert_candidate_after(i, candidate_to_add);
			i++;
			break;
		case 2:
			cin >> no;
			ret_code = remove_candidate(no);
			break;
		case 3:
			ret_code = show_candidates();
		};
		cout << ret_code << endl;
		cout << "Op N : ";
		cin >> op;
	};

	return 0;
}
