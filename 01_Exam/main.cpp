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

int main()
{
	int no, ret_code;
	string op;
	string candidate_name;
	int i = 0;

	cout << "[Op]# ";
	cin >> op;
	while (op != ":q")
	{
		ret_code = process_input(op);
		// exam_candidate *candidate_to_add = new exam_candidate;
		cout << "Return code is: " << ret_code << endl;

		cout << "[Op]# ";
		cin >> op;
	};

	return 0;
}
