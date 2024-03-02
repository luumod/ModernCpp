#include <iostream>
#include <string>
#include <concepts>
#include <type_traits>
#include <array>

//1. 非类型模板形参包展开：存储的是值
template <std::size_t...args>
void print() {
	for (const auto& x : { args... }) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}

//2. 类型模板形参包
template <typename...Args>
void print(Args&&...args) {
	((std::cout << args << ' '), ...);
	std::cout << '\n';
}

template <class T1, class T2,class T3>
struct X {};
//3. 模板模板形参包
template <template <class T,class T2,class T3> typename ... Args>
struct Y {};

//4. 类型约束
template <std::integral...Args>
void print2(Args&&...args) {
	(..., (std::cout << args << ' '));
	std::cout << '\n';
}

//1. is_same<T1,T2> 检查T1, T2是否处于相同的类型 并且 ... 依次展开
//2. conjunction<...> 得到 all 结果：true 或者 false
//3. are_same 传入整体参数包 std::decay_t<Args>...
template<typename T, typename... Args>
struct are_same : std::conjunction<std::is_same<T, Args>...> {};

template <typename...Args>
void printSameType(Args&&...args) {
	static_assert(are_same<std::decay_t<Args>...>::value, "All arguments must have the same type.");
	using common_type = std::common_type_t<Args...>;
	common_type values[sizeof...(args)]{ args... };
	for (const auto& x : values) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}

template <class...Fa>
struct overloaded :Fa...{
	using Fa::operator()...;
};

#if _HAS_CXX17
template <typename...Args>
void print_(Args&&...args) {
	((std::cout << args << ' '), ...);
}
#else
void print() {}
template <typename T,typename...Args>
void print(T&& t, Args&&...args) {
	std::cout << t << ' ';
	print(args...);
}
#endif

template <typename Array, typename...Args>
void value(const Array& array, Args&&...idx) {
	(print(array[idx]), ...);
}

template <typename Func, typename...Args>
void for_each(Func func, Args&&...args) {
#if _HAS_CXX17
	((func(args)), ...); //折叠表达式
#else
	int _[]{ ((func(args)),0)... };
#endif
}

template <typename...Args>
auto calcu(Args&&...args) {
	static auto list = { args + 2 * args ... };
	return list;
}
int main() {
	print<1,2,3,4,5>();
	print(1, 2, 3, 4.2, "awedad", 'a');
	Y<std::basic_string, X, X, X> y;
	print2(1, 2, 3, 4, 'a');

	printSameType(1, 2, 3, 4);
	printSameType(1.1, 2.2);
	printSameType('a','b');
	//func(1, "123");
	are_same<int, int,int,char>::value;

	auto f = overloaded{
				[](int a) {std::cout << a << '\n'; },
				[](double a) {std::cout << a << '\n'; },
				[](auto a) {std::cout << a << '\n'; } };
	f(1), f(2.1), f("str"), f(std::string("awdad"));

	print(1, 2, 3.2, '*', "woaini",'\n');

	//-------------------
	int nums[]{ 1,2,3,4,5 };
	value(nums, 0, 1, 2, 3, 4);

	std::cout << '\n';

	auto func = [](auto a) {std::cout << a << ' '; };
	for_each(func, 1, 3, 5, 7, 9);

	std::cout << '\n';

	auto res = calcu(1, 2, 3, 4, 5);
	for (const auto& x : res) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
	return 0;
}
