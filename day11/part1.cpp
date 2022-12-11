#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

struct Monkey {
	int inspected;
	deque<uint64_t> items;
	char op;
	int rhs;
	int divisor;
	int targets[2];
};

struct Tree {
	vector<Monkey> monkeys;
	decltype(monkeys)::size_type current;
	int rounds;
};

istream &operator>>(istream &in, Monkey &m) {
	m.inspected = 0;
	m.items.clear();
	string s;

	// Monkey n:
	while (getline(in, s) && s.substr(0, 6) != "Monkey") {}
	if (!in)
		return in;

	// Starting items: a, ..., b
	getline(in, s);
	s.erase(0, s.find(':') + 2);
	stringstream ss(s);
	while (getline(ss, s, ','))
		m.items.push_back(stoi(s));

	// Operation: new = old op rhs
	getline(in, s);
	auto i = s.rfind(" ");
	string rhs = s.substr(i + 1);
	if (rhs == "old")
		m.rhs = -1;
	else
		m.rhs = stoi(rhs);
	m.op = s[i - 1];

	// Test: divisible by n
	getline(in, s);
	m.divisor = stoi(s.substr(s.rfind(" ") + 1));

	// If true: throw to monkey n
	getline(in, s);
	m.targets[1] = stoi(s.substr(s.rfind(" ") + 1));

	// If false: throw to monkey n
	getline(in, s);
	m.targets[0] = stoi(s.substr(s.rfind(" ") + 1));

	return in;
}

istream &operator>>(istream &in, Tree &t) {
	t.monkeys.clear();
	copy(istream_iterator<Monkey>(in), {}, back_inserter(t.monkeys));

	t.current = 0;
	t.rounds = 0;
	return in;
}

void inspect(Tree &t) {
	Monkey &m = t.monkeys[t.current];

	auto item = m.items.front();
	m.items.pop_front();
	++m.inspected;

	auto rhs = item;
	if (m.rhs != -1)
		rhs = m.rhs;
	switch (m.op) {
	case '+': item += rhs; break;
	case '*': item *= rhs; break;
	}

	item /= 3;
	
	auto target = m.targets[item % m.divisor == 0];
	t.monkeys[target].items.push_back(item);
}

void turn(Tree &t) {
	while (!t.monkeys[t.current].items.empty())
		inspect(t);
	++t.current;
}

void round(Tree &t) {
	while (t.current < t.monkeys.size())
		turn(t);
	t.current = 0;
	++t.rounds;
}

uint64_t business(Tree &t) {
	vector<uint64_t> inspected;
	transform(t.monkeys.begin(), t.monkeys.end(), back_inserter(inspected),
		  [](const auto &m) { return m.inspected; });
	auto mid = inspected.begin() + 2;
	partial_sort(inspected.begin(), mid, inspected.end(), std::greater<int>());
	return inspected[0] * inspected[1];
}

int main() {
	Tree tree;
	cin >> tree;
	while (tree.rounds < 20)
		round(tree);
	cout << business(tree) << endl;
}
