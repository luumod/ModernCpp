#include <iostream>
#include <array>
#include <type_traits>
#include <vector>

template <typename T>
struct Test {
	Test(T a):a(a) {}
	T a;
};

Test(const char*) -> Test<std::string>;

template <typename T,std::size_t N>
struct array {
	T arr[N]{};
};


//自己实现
//is_same_v
template <typename T1, typename T2>
inline constexpr bool is_same_v = false;
template <typename T>
inline constexpr bool is_same_v<T, T> = true;

//enable_if_t
template <bool _Test, typename Type = void>
struct enable_if {};

template <typename _Ty>
struct enable_if<true, _Ty> {
	using type = _Ty;
};

template <bool _Test,typename _Ty = void>
using enable_if_t = typename enable_if<_Test, _Ty>::type;


template <typename Type, typename...Args>
/*
1. 一元右折叠保证参数包里都是相同类型
2. enable_if_t<true,Type> 保证Type为array的实际类型
3. sizeof...(args) + 1 保证array的长度

例如：array(1,2,3) -> array<int,3>
*/
array(Type, Args...) -> array<enable_if_t<(is_same_v<Type, Args>&&...), Type>, sizeof...(Args) + 1>;

int main() {
	Test a(1);
	Test a1(1.1);
	Test a2("sss");
	std::is_same<int, int>::value;

	std::array<int, 4> arr1{ 1,2,3,4 };
	std::array arr2{ 1,2,3,4,5,6,7,8,9,10 };
	array t{ 1,2,3,4,5,6 };

	std::vector vec{ 1,2,3,4 };
	return 0;
}