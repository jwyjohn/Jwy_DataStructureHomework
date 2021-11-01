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
	int no, ret_code;
	char op;
	string candidate_name;
	cin >> op;
	int i = 0;
	while (op != EOF)
	{
		exam_candidate *candidate_to_add = new exam_candidate;
		switch (op)
		{
		case 'A':
			cin >> i >> no >> candidate_name;
			candidate_to_add->No = no;
			candidate_to_add->name = candidate_name;
			ret_code = insert_candidate_after(i, candidate_to_add);
			i++;
			break;
		case 'R':
			cin >> no;
			ret_code = remove_candidate(no);
			break;
		case 'S':
			ret_code = show_candidates();
			break;
		default:
			cout << "Unknown command" << endl;
			ret_code = 1;
		};
		cout << "Return code is" << ret_code << endl;
		cout << "Op N : ";
		cin >> op;
	};

	return 0;
}
