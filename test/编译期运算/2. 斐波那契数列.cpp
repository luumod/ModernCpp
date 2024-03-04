#include <iostream>

//斐波那契数列
template <std::size_t val>
struct Fibonacci {
	static constexpr auto value = Fibonacci<val - 1>::value + Fibonacci<val - 2>::value;
};

template <>
struct Fibonacci<1> {
	static constexpr auto value = 1;
};

template <>
struct Fibonacci<0> {
	static constexpr auto value = 0;
};

template <size_t N>
static constexpr auto Fibonacci_v = Fibonacci<N>::value;

int main() {
	constexpr std::size_t i = 10;
	constexpr auto f1 = Fibonacci<i>::value;
	constexpr auto f2 = Fibonacci_v<22>;

	return 0;
}
