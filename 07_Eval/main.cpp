#include "eval.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	cout << "Testing.." << endl;
	cin >> s;
	exp *tes = new exp(s);
	return 0;
}
