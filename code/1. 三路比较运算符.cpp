#include <iostream>

struct Test {
	int v{};
	int operator-(const Test& t)const noexcept {
		return this->v - t.v;
	}
	/*friend auto operator<=>(const Test& a, const Test& b)noexcept {
		if (a - b < 0) return -1;
		else if (a - b > 0) return 1;
		else return 0;
	}*/

	auto operator<=>(const Test& a)const noexcept = default;
};

int main() {
	int a = 2, b = 2;
	auto ans = a <=> b;
	if (ans < 0) {
		std::cout << "a<b\n";
	}
	else if (ans > 0) {
		std::cout << "a>b\n";
	}
	else {
		std::cout << "a=b\n";
	}

	Test q{}, w{};
	std::cout << (int)(q <=> w)._Value << '\n';
	std::cout << (q > w) << '\n';
	std::cout << (q >= w) << '\n';
	std::cout << (q < w) << '\n';
	std::cout << (q <= w) << '\n';
	std::cout << (q == w) << '\n';
	
	return 0;
}