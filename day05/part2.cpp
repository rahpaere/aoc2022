#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
	vector<vector<char>> stacks;

	string line;
	while (getline(cin, line) && line.find('[') != string::npos) {
		for (int i = 1; i < line.size(); i += 4) {
			if (line[i] == ' ')
				continue;
			int n = (i - 1) / 4;
			if (n >= stacks.size())
				stacks.resize(n + 1);
			stacks[n].push_back(line[i]);
		}
	}
	for (auto &stack: stacks)
		ranges::reverse(stack);

	string move, from, to;
	int n, src, dst;
	while (cin >> move >> n >> from >> src >> to >> dst) {
		--src, --dst;
		copy_n(stacks[src].end() - n, n, back_inserter(stacks[dst]));
		stacks[src].erase(stacks[src].end() - n, stacks[src].end());
	}
	
	for (const auto &stack: stacks)
		cout << stack.back();
	cout << endl;
}
