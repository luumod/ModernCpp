#include <vector>
#include <array>

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

//编译期获取序列值
template <size_t...args>
constexpr auto get(std::index_sequence<args...>) {
	return std::array<int, sizeof...(args)>{Fibonacci_v<args>...};
}

template <size_t range>
constexpr auto vector() {
	return get(std::make_index_sequence<range>{});
}

int main() {
	constexpr std::size_t numValues = 10;
	constexpr auto v = vector<10>();
	std::vector<int> vec{ v.begin(), v.end() };
	return 0;
}
