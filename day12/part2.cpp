#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Move {
	int cost { numeric_limits<decltype(cost)>::max() };
	pair<int, int> step {};
};

ostream &operator<<(ostream &out, const vector<vector<Move>> &moves) {
	for (const auto &row: moves) {
		for (const auto &move: row) {
			if (move.cost == numeric_limits<decltype(move.cost)>::max())
				cout << '.';
			else if (move.cost == 0)
				cout << 'E';
			else if (move.step == make_pair(-1, 0))
				cout << '^';
			else if (move.step == make_pair(1, 0))
				cout << 'v';
			else if (move.step == make_pair(0, -1))
				cout << '<';
			else if (move.step == make_pair(0, 1))
				cout << '>';
		}
		out << '\n';
	}
	return out;
}

int main() {
	vector<vector<int>> map;
	pair<int, int> start;
	pair<int, int> end;

	string line;
	while (getline(cin, line)) {
		vector<int> row;
		for (char c: line) {
			switch (c) {
			case 'S':
				start = make_pair(map.size(), row.size());
				row.push_back(0);
				break;
			case 'E':
				end = make_pair(map.size(), row.size());
				row.push_back(25);
				break;
			default:
				row.push_back(c - 'a');
			}
		}
		map.emplace_back(move(row));
	}

	int rows = static_cast<int>(map.size());
	int cols = static_cast<int>(map.front().size());

	vector<vector<Move>> moves(rows, vector<Move>(cols));
	moves[end.first][end.second].cost = 0;

	bool changed;
	do {
		changed = false;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				for (int di = -1; di <= 1; ++di) {
					for (int dj = -1; dj <= 1; ++dj) {
						if ((di != 0) != (dj != 0) && i + di >= 0 && i + di < rows && j + dj >= 0 && j + dj < cols) {
							auto cost = moves[i + di][j + dj].cost;
							if (cost == numeric_limits<decltype(cost)>::max() || map[i + di][j + dj] > map[i][j] + 1)
								continue;
							Move m { cost + 1, { di, dj } };
							if (m.cost < moves[i][j].cost) {
								moves[i][j] = m;
								changed = true;
							}
						}
					}
				}
			}
		}
	} while (changed);

	int cost = moves[start.first][start.second].cost;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (map[i][j] == 0)
				cost = min(cost, moves[i][j].cost);
	
	cout << cost << endl;
}
