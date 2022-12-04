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

struct Assignment {
	int from;
	int to;
};

struct Pair {
	Assignment first;
	Assignment other;
};

istream &operator>>(istream &in, Assignment &a) {
	char hyphen;
	return in >> a.from >> hyphen >> a.to;
}

istream &operator>>(istream &in, Pair &p) {
	char comma;
	return in >> p.first >> comma >> p.other;
}

ostream &operator<<(ostream &out, const Assignment &a) {
	return out << a.from << '-' << a.to;
}

ostream &operator<<(ostream &out, const Pair &p) {
	return out << p.first << ',' << p.other;
}

bool contains(const Pair &p) {
	return    (p.first.from >= p.other.from && p.first.to <= p.other.to)
	       || (p.first.from <= p.other.from && p.first.to >= p.other.to);
}

bool overlaps(const Pair &p) {
	return p.first.from <= p.other.to && p.first.to >= p.other.from;
}

int main() {
	vector<Pair> pairs;
	copy(istream_iterator<Pair>(cin), {}, back_inserter(pairs));
	cout << count_if(pairs.begin(), pairs.end(), overlaps) << endl;
}
