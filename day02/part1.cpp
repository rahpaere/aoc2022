#include <algorithm>
#include <bitset>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <variant>
#include <vector>

using namespace std;

int main() {
	char other, self;

	int total = 0;
	while (cin >> other >> self) {

		other -= 'A';
		self -= 'X';

		int round = self + 1;
		if ((other + 1) % 3 == self)
			round += 6;
		else if (other == self)
			round += 3;

		cout << round << endl;
		total += round;
	}

	cout << endl << total << endl;
}
