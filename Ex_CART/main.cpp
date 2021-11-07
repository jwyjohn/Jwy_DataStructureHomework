#include "CART.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Testing.." << endl;
	dataset D(10, 3, 2);
	D.category = {0, 0, 0, 0, 1, 0, 0, 1, 0, 1};
	D.feature[0] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0};
	D.feature[1] = {0.0, 1.0, 0.0, 1.0, 2.0, 1.0, 2.0, 0.0, 1.0, 0.0};
	D.feature[2] = {125.0, 100.0, 70.0, 120.0, 95.0, 60.0, 220.0, 85.0, 75.0, 90.0};

	// cout << calc_gini(D) << endl;
	// cout << calc_split_gini(D, 2, 80.0) << endl;
	// for (auto &item : gen_split(D, 2))
	// {
	// 	cout << " " << item;
	// }
	// cout << endl;

	// find_split(D);

	// split_pair tmp = gen_split_pair(D);
	// for (auto &item : tmp.A.category)
	// {
	// 	cout << " " << item;
	// }
	// cout << endl;
	// for (auto &item : tmp.B.category)
	// {
	// 	cout << " " << item;
	// }
	// cout << endl;
	int N = 4;
	stack<split_pair> s;
	s.push(gen_split_pair(D));
	while (N > 0 && !s.empty())
	{
		N--;
		dataset tmpA = s.top().A;
		dataset tmpB = s.top().B;
		cout << s.top().split.no << ": " << s.top().split.threshold << endl;
		s.pop();
		if (tmpA.size > 1)
			s.push(gen_split_pair(tmpA));
		if (tmpB.size > 1)
			s.push(gen_split_pair(tmpB));
		cout << " - " << tmpA.size << " " << tmpB.size << endl;
	};
	cout << "DONE!" << endl;
	// while (!s.empty())
	// {
	// 	cout << s.top().split.no << ": " << s.top().split.threshold << endl;
	// 	s.pop();
	// };
	return 0;
}
