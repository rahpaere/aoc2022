#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>

using namespace std;

int main() {
	array<char, 14> buffer;
	copy_n(istream_iterator<char>(cin), buffer.size(), begin(buffer));

	int n = buffer.size();
	for (;;) {
		auto s = buffer;
		ranges::sort(s);
		if (ranges::unique(s).begin() == end(s))
			break;
		cin >> buffer[n++ % buffer.size()];
	}

	cout << n << endl;
}
