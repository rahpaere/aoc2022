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

int priority(char c) {
	return isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
}

int main() {
	vector<string> rucksacks;
	copy(istream_iterator<string>(cin), {}, back_inserter(rucksacks));

	int sum = 0;
	for (auto &sack: rucksacks) {
		auto mid = sack.begin() + sack.size() / 2;
		sort(sack.begin(), mid);
		sort(mid, sack.end());

		string misplaced;
		set_intersection(sack.begin(), mid, mid, sack.end(), back_inserter(misplaced));
		
		sum += priority(misplaced[0]);
	}

	cout << sum << endl;
}
