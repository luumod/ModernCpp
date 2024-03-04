#include <iostream>

template <int N>
struct Factorial {
	static constexpr auto value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial<0> {
	static constexpr auto value = 1;
};

template <int N>
static constexpr auto Factorial_v = Factorial<N>::value;

int main() {
	constexpr auto num = Factorial<5>::value;
	constexpr auto num2 = Factorial_v<6>;
	return 0;
}
