#include <iostream>
#include <map>

template <typename T>
struct Test {
	int num;
};

int main() {
	std::map<int, std::pair<int, int>> mp;
	for (int i = 0; i < 3; i++) {
		mp.emplace(i, std::make_pair<int, int>(i + 1, i - 1));
	}
	for (const auto& [i, p] : mp) {
		std::cout << "num: " << i << ' ' << p.first << " " << p.second << '\n';
	}
	return 0;
}