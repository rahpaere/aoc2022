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

struct Elf {
	int snacks;
	int calories;
};

istream &operator>>(istream &in, Elf &elf) {
	elf.snacks = 0;
	elf.calories = 0;

	string line;
	while (getline(in, line) && !line.empty()) {
		elf.snacks++;
		elf.calories += stoi(line);
	}

	if (elf.snacks == 0)
		in.setstate(std::ios::failbit);
	else
		in.clear();
	return in;
}

bool operator<(const Elf &a, const Elf &b) {
	return a.calories > b.calories;
}

int operator+(int a, const Elf &b) {
	return a + b.calories;
}

int main() {
	vector<Elf> elves;
	copy(istream_iterator<Elf>(cin), {}, back_inserter(elves));
	auto middle = begin(elves) + 3;
	partial_sort(begin(elves), middle, end(elves)); 
	cout << accumulate(begin(elves), middle, 0) << endl;
}
