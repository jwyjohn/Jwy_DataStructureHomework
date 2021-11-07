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
	// int N = 4;
	// while (N > 0)
	// {
	// 	N--;
	// };
	find_split(D);
	return 0;
}
