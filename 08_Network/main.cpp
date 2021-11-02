#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include "network.h"
using namespace std;

int main()
{
	int no, ret_code;
	string op;
	enetwork elec;
	while (op != "STOP233")
	{
		cin >> op;
		if (op == "A")
		{
			string v;
			cin >> v;
			elec.add_node(v);
		}
		else if (op == "B")
		{
			string a, b;
			int c;
			cin >> a >> b >> c;
			elec.add_edge(a, b, c);
		}
		else if (op == "S")
		{
			elec.print_edges();
			string s;
			cin >> s;
			elec.run_prim(s);
		}
	};
	return 0;
}
