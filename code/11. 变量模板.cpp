#include <iostream>

template <typename T1,typename T2>
struct is_same {
	using value = false;
};

template <typename T>
struct is_same<T,T> {
	using value = true;
};

template <typename T1,typename T2>
constexpr auto is_same_v = false;

template <typename T>
constexpr auto is_same_v<T,T> = true;

int main() {
	constexpr auto p1 = is_same_v<int, int>;
	constexpr auto p2 = is_same_v<int, int*>;
	constexpr auto p3 = std::is_same<int, int>::value;
	constexpr auto p4 = std::is_same<double, int>::value;
	return 0;
}
