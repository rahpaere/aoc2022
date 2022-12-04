#include <algorithm>
#include <iostream>
#include <iterator>

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

bool overlaps(const Pair &p) {
	return max(p.first.from, p.other.from) <= min(p.first.to, p.other.to);
}

int main() {
	vector<Pair> pairs;
	copy(istream_iterator<Pair>(cin), {}, back_inserter(pairs));
	cout << count_if(pairs.begin(), pairs.end(), overlaps) << endl;
}
