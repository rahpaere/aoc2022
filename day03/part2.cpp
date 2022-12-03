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
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <variant>
#include <vector>

using namespace std;

struct Group {
	array<string, 3> elves;
};

istream &operator>>(istream &in, Group &g) {
	for (auto &sack: g.elves) {
		in >> sack;
		ranges::sort(sack);
	}
	return in;
}

int priority(char c) {
	return isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
}

char common_item(const Group &g) {
	string a, b;
	ranges::set_intersection(g.elves[0], g.elves[1], back_inserter(a));
	ranges::set_intersection(g.elves[2], a, back_inserter(b));
	return b.front();
}

int main() {
	vector<Group> groups;
	copy(istream_iterator<Group>(cin), {}, back_inserter(groups));

	int sum = 0;
	for (auto i: groups | views::transform(common_item) | views::transform(priority))
		sum += i;
	cout << sum << endl;
}
