#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
	vector<string> forest;
	copy(istream_iterator<string>(cin), {}, back_inserter(forest));

	vector<vector<int>> heights;
	for (const auto &row: forest) {
		auto &height_row = heights.emplace_back();
		transform(row.begin(), row.end(), back_inserter(height_row),
			  [](char c) { return c - '0'; });
	}

	int rows = static_cast<int>(heights.size());
	int cols = static_cast<int>(heights[0].size());

	vector<vector<int>> clearances(rows, vector<int>(cols));

	// set up initial clearances, from the left
	for (int i = 0; i < rows; ++i) {
		clearances[i][0] = -1;
		for (int j = 1; j < cols; ++j)
			clearances[i][j] = max(clearances[i][j - 1], heights[i][j - 1]);
	}

	// update clearances, from the right
	for (int i = 0; i < rows; ++i) {
		int clearance = -1;
		clearances[i][cols - 1] = clearance;
		for (int j = cols - 2; j >= 0; --j) {
			clearance = max(clearance, heights[i][j + 1]);
			clearances[i][j] = min(clearances[i][j], clearance);
		}
	}

	// update clearances, from the top
	for (int j = 0; j < cols; ++j) {
		int clearance = -1;
		clearances[0][j] = clearance;
		for (int i = 1; i < rows; ++i) {
			clearance = max(clearance, heights[i - 1][j]);
			clearances[i][j] = min(clearances[i][j], clearance);
		}
	}

	// update clearances, from the bottom
	for (int j = 0; j < cols; ++j) {
		int clearance = -1;
		clearances[rows - 1][j] = clearance;
		for (int i = rows - 2; i >= 0; --i) {
			clearance = max(clearance, heights[i + 1][j]);
			clearances[i][j] = min(clearances[i][j], clearance);
		}
	}

	unsigned n = 0;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			n += heights[i][j] > clearances[i][j];
	cout << n << endl;
}
