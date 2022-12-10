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

	int getTotal() { return total; }

private:
	int total {};
	int cycle {};
	int x = 1;

	void step() {
		++cycle;
		if ((cycle + 20) % 40 == 0)
			total += cycle * x;
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

	cout << d.getTotal() << endl;
}
