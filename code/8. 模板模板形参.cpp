#include <iostream>
#include <vector>

template <typename T>
struct X {
	int num;
};

template <typename T, template <typename T> typename S>
struct Y {
	S<T> s;
};

//std::vector
template <typename _Ty,template <class _Ty, class _Alloc = std::allocator<_Ty>> typename Vec>
struct vector {
	Vec<_Ty> v;

	template <typename...Args>
	void push_back(Args&&...args) {
		static_assert((std::is_constructible_v<Vec<_Ty>,Args&&> && ...), "参数接收错误");
		(v.push_back(std::forward<Args>(args)), ...);
	}
};

//std::basic_string
template <template <class T,class T2,class T3> typename S>
struct string {
	S<char, std::char_traits<char>, std::allocator<char>> str;
	S<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> wstr;
};

int main() {
	Y<int, X> y;
	y.s.num = 1;

	vector<int, std::vector> my_v{};
	my_v.push_back(1, 2, 3, 4, 5, 6);
	my_v.push_back(7, 8, 9, 10);
	for (const auto& x : my_v.v) {
		std::cout << x<<' ';
	}
	std::cout << '\n';

	string<std::basic_string> my_str;
	my_str.str = "ylh";
	my_str.wstr = L"wylh";
	std::cout << my_str.str << '\n';
	std::wcout << my_str.wstr << '\n';
	return 0;
}
