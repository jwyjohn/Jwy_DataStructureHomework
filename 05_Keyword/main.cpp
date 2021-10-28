#include "KMP.h"
#include <iostream>
#include<string>

using namespace std;

int main()
{
	string x,s;
	cout << "Testing.." << endl;
	cin>>x;
	cin>>s;
	text kmp(x);
	cout<<kmp.countWord(s)<<endl;

	return 0;
}
