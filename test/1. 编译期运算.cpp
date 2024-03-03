#include <iostream>
#include <array>
#include <utility>
#include <vector>
//阶乘
template <std::size_t val>
struct factorial {
	static constexpr auto value = val * factorial<val - 1>::value;
};
template <>
struct factorial<0> {
	static constexpr auto value = 1;
};

template <std::size_t val>
static constexpr auto factorial_v = factorial<val>::value;

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

template <std::size_t val>
static constexpr auto Fibonacci_v = Fibonacci<val>::value;

//编译期获取序列值
template <size_t...args>
constexpr auto get(std::index_sequence<args...>) {
	return std::array<int, sizeof...(args)>{Fibonacci_v<args>...};
}

template <size_t range>
constexpr auto vector() {
	return get(std::make_index_sequence<range>{});
}

//编译期求幂运算
template <size_t base,size_t exponent>
struct Power {
	static constexpr auto value = base * Power<base, exponent - 1>::value;
};
template <size_t base>
struct Power<base, 0> {
	static constexpr auto value =1;
};

int main() {
	constexpr auto num = factorial<5>::value;
	constexpr auto num2 = factorial_v<6>;

	constexpr std::size_t i = 10;
	constexpr auto f1 = Fibonacci<i>::value;
	constexpr auto f2 = Fibonacci_v<7>;

	constexpr std::size_t numValues = 10;

	constexpr auto v = vector<10>();
	std::vector<int> vec{ v.begin(), v.end() };

	constexpr auto c = Power<2, 60>::value;
	return 0;
}
