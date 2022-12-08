#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int score(const vector<vector<int>> &heights, int row, int col) {
	int rows = static_cast<int>(heights.size());
	int cols = static_cast<int>(heights[0].size());

	if (row == 0 || col == 0 || row == rows - 1 || col == cols - 1)
		return 0;
	
	int r = 1;
	while (col + r < cols - 1 && heights[row][col + r] < heights[row][col])
		++r;

	int l = 1;
	while (col - l > 0 && heights[row][col - l] < heights[row][col])
		++l;

	int t = 1;
	while (row - t > 0 && heights[row - t][col] < heights[row][col])
		++t;

	int b = 1;
	while (row + b < rows - 1 && heights[row + b][col] < heights[row][col])
		++b;

	return r * l * t * b;
}

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

	int best = 0;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			best = max(best, score(heights, i, j));
	cout << best << endl;
}
