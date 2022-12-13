#include <algorithm>
#include <iostream>
#include <iterator>
#include <variant>
#include <vector>

using namespace std;

struct Packet {
	variant<int, vector<Packet>> content;
};

istream &operator>>(istream &in, Packet &p);

istream &operator>>(istream &in, vector<Packet> &v) {
	v.clear();

	in.ignore(); // [
	if (in.peek() == ']') {
		in.ignore();
		return in; // empty list
	}

	Packet p;
	while (in >> p) {
		v.emplace_back(move(p));
		char c;
		in >> c; // , or ]
		if (c == ']')
			return in;
	}
	return in;
}

istream &operator>>(istream &in, Packet &p) {
	in >> ws;
	if (in.peek() == '[') {
		vector<Packet> v;
		in >> v;
		p.content = move(v);
	} else {
		int n;
		in >> n;
		p.content = n;
	}
	return in;
}

ostream &operator<<(ostream &out, const Packet &p);

ostream &operator<<(ostream &out, const vector<Packet> &v) {
	out << '[';
	if (v.empty())
		return out << ']';
	out << v.front();
	for (auto it = v.begin() + 1; it != v.end(); ++it)
		out << ',' << *it;
	return out << ']';
}

ostream &operator<<(ostream &out, const Packet &p) {
	visit([&out](const auto &x) { out << x; }, p.content);
	return out;
}

using PacketPair = pair<Packet, Packet>;

istream &operator>>(istream &in, PacketPair &pp) {
	return in >> pp.first >> pp.second;
}

struct PacketComparison {
	bool operator()(int a, int b) {
		return a < b;
	}

	bool operator()(const vector<Packet> &a, const vector<Packet> &b) {
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	bool operator()(int a, const vector<Packet> &b) {
		return (*this)(vector<Packet> { { a } }, b);
	}

	bool operator()(const vector<Packet> &a, int b) {
		return (*this)(a, vector<Packet> { { b } });
	}
};

bool operator<(const Packet &a, const Packet &b) {
	return visit(PacketComparison(), a.content, b.content);
}

int main() {
	vector<PacketPair> pairs;
	copy(istream_iterator<PacketPair>(cin), {}, back_inserter(pairs));

	int total = 0;
	for (decltype(pairs)::size_type i = 0; i < pairs.size(); ++i) {
		if (!(pairs[i].second < pairs[i].first)) 
			total += i + 1;
	}
	cout << total << endl;
}
