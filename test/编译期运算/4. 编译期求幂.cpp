#include <iostream>

//编译期求幂运算
template <size_t base, size_t exponent>
struct Power {
	static constexpr auto value = base * Power<base, exponent - 1>::value;
};
template <size_t base>
struct Power<base, 0> {
	static constexpr auto value = 1;
};

int main() {
	constexpr auto c = Power<2, 5>::value;
	return 0;
}
