#include <algorithm>
#include <bitset>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <variant>
#include <vector>

using namespace std;

int main() {
	int most = 0;
	int current = 0;
	string line;
	while (getline(cin, line)) {
		if (line.empty()) {
			most = max(most, current);
			current = 0;
		} else {
			current += stoi(line);
		}
	}
	cout << most << endl;
}
