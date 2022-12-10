#include <iostream>
#include <array>

using namespace std;

class Device {
public:
	void noop() {
		step();
	}

	void addx(int v) {
		step();
		step();
		x += v;
	}

private:
	int pixel = 0;
	int x = 1;

	static constexpr array<char, 2> symbols { '.', '#' };

	void step() {
		cout << symbols[abs(pixel - x) <= 1];
		pixel = (pixel + 1) % 40;
		if (pixel == 0)
			cout << '\n';
	}
};

int main() {
	Device d;

	string op;
	while (cin >> op) {
		if (op == "addx") {
			int v;
			cin >> v;
			d.addx(v);
		} else {
			d.noop();
		}
	}
}
