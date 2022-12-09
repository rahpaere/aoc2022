#include <array>
#include <iostream>
#include <iterator>
#include <set>
#include <tuple>

using namespace std;

struct Point {
	int x {};
	int y {};
};

Point operator-(const Point &a, const Point &b) {
	return { a.x - b.x, a.y - b.y };
}

bool operator<(const Point &a, const Point &b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

ostream &operator<<(ostream &out, const Point &p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

int signum(int x) {
	return (x > 0) - (x < 0);
}

void link(Point &tail, const Point &head) {
	Point d = head - tail;
	if (abs(d.x) > 1 || (abs(d.y) > 1 && abs(d.x) > 0))
		tail.x += signum(d.x);
	if (abs(d.y) > 1 || (abs(d.x) > 1 && abs(d.y) > 0))
		tail.y += signum(d.y);
}

template<typename Iterator>
void link(Iterator first, Iterator last) {
	if (first == last)
		return;
	auto other = first + 1;
	while (other != last)
		link(*other++, *first++);
}

void step(Point &p, char direction) {
	switch (direction) {
	case 'R': ++p.x; break;
	case 'U': ++p.y; break;
	case 'L': --p.x; break;
	case 'D': --p.y; break;
	};
}

int main() {
	array<Point, 10> rope;
	set<Point> visited { rope.back() };

	char direction;
	int steps;
	while (cin >> direction >> steps) {
		for (int i = 0; i < steps; ++i) {
			step(rope.front(), direction);
			link(rope.begin(), rope.end());
			visited.insert(rope.back());
		}
	}

	cout << visited.size() << endl;
}
