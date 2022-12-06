#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <iterator>
#include <numeric>

using namespace std;

struct CharBit {
	uint32_t bit {};
};

istream &operator>>(istream &in, CharBit &cb) {
	char c;
	in >> c;
	cb.bit = 1 << (c - 'a');
	return in;
}

CharBit operator+(const CharBit &a, const CharBit &cb) {
	return { a.bit | cb.bit };
}

int weight(const CharBit &cb) {
	return popcount<uint32_t>(cb.bit);
}

int main() {
	array<CharBit, 14> buffer;
	int n = buffer.size();
	copy_n(istream_iterator<CharBit>(cin), n, begin(buffer));
	while (weight(accumulate(begin(buffer), end(buffer), CharBit{})) != buffer.size())
		cin >> buffer[n++ % buffer.size()];
	cout << n << endl;
}
