#include <iostream>

using namespace std;

int main() {
	int score = 0;

	char other, self;
	while (cin >> other >> self) {
		other -= 'A';
		self -= 'X';

		score += self + 1;
		if ((other + 1) % 3 == self)
			score += 6;
		else if (other == self)
			score += 3;
	}

	cout << score << endl;
}
