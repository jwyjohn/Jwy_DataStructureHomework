#include "BT.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Testing.." << endl;
	bt_node<int> *root = new bt_node<int>;
	bt_node<int> *l1 = new bt_node<int>;
	bt_node<int> *r1 = new bt_node<int>;
	root->val = 62;
	root->lc = l1;
	root->rc = r1;
	l1->val = 11;
	r1->val = 90;
	int val;
	while (true)
	{
		cin >> val;
		insert_bt(root, val);
		print_bt(root);
		cout << endl;
	};
	return 0;
}
