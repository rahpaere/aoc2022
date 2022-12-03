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

struct Group {
	array<string, 3> elves;
};

istream &operator>>(istream &in, Group &g) {
	for (auto &sack: g.elves) {
		in >> sack;
		sort(sack.begin(), sack.end());
	}
	return in;
}

int priority(char c) {
	return isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
}

char common_item(const Group &g) {
	string tmp;
	set_intersection(g.elves[0].begin(), g.elves[0].end(),
			 g.elves[1].begin(), g.elves[1].end(),
			 back_inserter(tmp));
	string common;
	set_intersection(g.elves[2].begin(), g.elves[2].end(),
			 tmp.begin(), tmp.end(),
			 back_inserter(common));
	return common[0];
}

int main() {
	vector<Group> groups;
	copy(istream_iterator<Group>(cin), {}, back_inserter(groups));

	int sum = 0;
	for (const auto &group: groups)
		sum += priority(common_item(group));
	cout << sum << endl;
}
