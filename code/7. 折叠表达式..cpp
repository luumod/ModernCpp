#include <iostream>
#include <vector>
#include <utility>
#include <array>

template <typename...Args>
constexpr auto sum(const Args&...args) noexcept {
	return (args + ... + 0);
}

template <typename...Args>
constexpr auto product(const Args&...args) noexcept {
	return (args * ...  * 1);
}

template <typename...Args>
constexpr auto all(const Args&...args) noexcept {
	return (args && ...);
}

template <typename...Args>
constexpr auto any(const Args&...args)noexcept {
	return (args || ...);
}


template <typename...Args>
void printR(const Args&...args) {
	//一元右折叠： 形参包 运算符 ...
	((std::cout << args << ' '), ...) << '\n';
}
template <typename...Args>
void printL(const Args& ...args) {
	//一元左折叠
	(..., (std::cout << args << ' ')) << '\n';
}

template <int...Args>
inline constexpr int v_right = (Args - ...);

template <int...Args>
inline constexpr int v_left = (... - Args);

template <int...Args>
inline constexpr int vv_left = (10 + ... + Args);

template <int...Args>
inline constexpr int vv_right = (Args + ... + 10);

template <typename Cont,typename...Args>
void push_back_vector(Cont& vector, Args&&...args) {
	static_assert( (std::is_constructible_v<Cont, Args&&> && ...),"容器无法从参数中构造");
	(vector.push_back(std::forward<Args>(args)), ...);
}

template <typename Func,typename...Args>
void for_each(Func&& func, Args&&...args) {
	(func(args), ...);
}

template<class T>
constexpr auto max(T t)
{
	return t;
}

template<class T, class ...Args>
constexpr auto max(T t, Args... args)
{
	T tmp = max(args...);
	return t > tmp ? t : tmp;
}

int main() {
	constexpr auto p = sum(1.1, 2, 3, 4, 5);
	constexpr auto p1 = all(true, true,false);
	constexpr auto p1_ = any(true, true, false);
	constexpr auto p2 = product(1, 2, 3, 4, 5);
	constexpr auto p3 = sum();
	constexpr auto p4 = product(); //二元表达式给定初值使其接收空参数，否则需要特化

	printR(1, 2.9999, 'a', "111");
	printL(1, 2.9999, 'a', "111");

	constexpr auto n1 = v_right<1, 2, 3>; // (1 - (2 - 3))
	constexpr auto n2 = v_left<1, 2, 3>;  // ((1 - 2) - 3)
	constexpr auto n3 = vv_right<1, 2, 3>;// (10 + (1 + (2 + 3)))
	constexpr auto n4 = vv_left<1, 2, 3>; // (((10 + 1) + 2) + 3))

	std::vector<int> v{ 1,2,3,4 };
	push_back_vector(v, 5, 6, 7, 8, 9, 10);
	//push_back_vector("11", "22", "33");
	for (const auto& x : v) {
		std::cout << x << ' ';
	}
	std::cout << '\n';


	for_each([](auto a) { std::cout << a << ' '; }, 1, 2, 3, 4, 5, 6,'\n');
	for_each([](auto a) { std::cout << a << ' '; }, 1, 2, 3, 4, 5, 6,'\n');
	
	std::cout << max(11, 2, 3, 4, 5) << '\n';
	return 0;
}