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
	bool step = d.x * d.x + d.y * d.y > 2;
	tail.x += step * signum(d.x);
	tail.y += step * signum(d.y);
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
	Point head, tail;
	set<Point> visited { tail };

	char direction;
	int steps;
	while (cin >> direction >> steps) {
		for (int i = 0; i < steps; ++i) {
			step(head, direction);
			link(tail, head);
			visited.insert(tail);
		}
	}

	cout << visited.size() << endl;
}
