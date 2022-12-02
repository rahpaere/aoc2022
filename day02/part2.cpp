#include <iostream>

using namespace std;

int main() {
	int score = 0;

	char other, self;
	while (cin >> other >> self) {
		other -= 'A';
		self -= 'X';

		score += 3 * self;
		score += (other + self + 2) % 3 + 1;
	}

	cout << score << endl;
}
