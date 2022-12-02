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

		int round = 0;

		if (self == 'X') {
			round = 0;
			self = (other + 2) % 3;
		} else if (self == 'Y') {
			round = 3;
			self = other;
		} else {
			round = 6;
			self = (other + 1) % 3;
		}

		round += self + 1;

		cout << round << endl;
		total += round;
	}

	cout << endl << total << endl;
}
