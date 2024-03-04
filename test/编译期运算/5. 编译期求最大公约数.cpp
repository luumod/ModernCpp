#include <iostream>

//编译期求两个数字的最大公约数
template <int M, int N>
struct GCD {
	static constexpr auto value = GCD<N, M% N>::value;
};

template <int A>
struct GCD<A, 0> {
	static constexpr auto value = A;
};

int main() {
	constexpr auto g = GCD<4, 16>::value;
	std::cout << g << '\n';
	return 0;
}
