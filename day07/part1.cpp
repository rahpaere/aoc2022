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

struct Entry {
	string name {};
	unsigned size {};
	Entry *parent {};
	vector<Entry> children {};

	Entry(const string &name, Entry *parent = nullptr): name(name), parent(parent) {}
};

Entry &child(Entry &e, const string &name) {
	auto it = find_if(e.children.begin(), e.children.end(), [&name](auto &x) { return x.name == name; });
	if (it != e.children.end())
		return *it;
	return e.children.emplace_back(name, &e);
}

void print(ostream &out, const Entry &e, string prefix = "") {
	out << prefix << "- " << e.name << " (";
	if (e.children.empty() && e.size > 0) {
		out << "file, size=" << e.size << ")\n";
	} else {
		out << "dir)\n";
		for (const auto &child: e.children)
			print(out, child, prefix + "  ");
	}
}

unsigned cumulative_size(const Entry &e) {
	unsigned size = e.size;
	for (const auto &child: e.children)
		size += cumulative_size(child);
	cout << "cumulative size of " << e.name << " is " << size << endl;
	return size;
}

unsigned candidate_size(const Entry &e) {
	unsigned size = cumulative_size(e);
	if (size > 100000)
		size = 0;
	for (const auto &child: e.children)
		if (!child.children.empty())
			size += candidate_size(child);
	return size;
}

int main() {
	Entry root { "/" };
	Entry *current = &root;

	string line;
	while (getline(cin, line)) {
		if (line.front() == '$') {
			stringstream s { line };
			s.ignore(); // throw away prompt
			string command;
			s >> command;
			if (command == "cd") {
				string dst;
				s >> dst;
				if (dst == "..")
					current = current->parent;
				else if (dst == "/")
					current = &root;
				else
					current = &child(*current, dst);
			}
			// do nothing for ls, ignore invalid commands
		} else {
			stringstream s { line };
			string info, name;
			s >> info >> name;
			if (info == "dir")
				child(*current, name);
			else
				child(*current, name).size = stoi(info);
		}
	}

	cout << candidate_size(root) << endl;
}
