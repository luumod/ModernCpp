#include <iostream>

//模板的全特化
template <typename _Ty>
struct X {
	void f() {
		std::cout << "origin" << '\n';
	}
};

template <>
struct X<double> {
	void f() {
		std::cout << "Full Specialization" << '\n';
	}
};

//模板的偏特化
template <typename T,std::size_t N>
struct Y {
	void p() {
		std::cout << "origin Y\n";
	}
};

template <typename T,std::size_t N>
struct Y<T*, N> {
	void p() {
		std::cout << "Partial Specialization" << '\n';
	}
};

template <typename T>
constexpr bool is_const_v = false;

template <typename T>
constexpr bool is_const_v<const T> = true;

int main(){
	X<int> x;
	x.f();
	X<double> x2;
	x2.f();

	Y<int, 10> y;
	y.p();
	Y<int*, 100> y2;
	y2.p();
	Y<const int*, 23> y3;
	y3.p();
	Y<std::string*, 22> y4;
	y4.p();
	Y<X<int>*, 10> y5;
	y5.p();

	std::type_identity<double>::type;

	constexpr auto p = is_const_v<const int>;
	constexpr auto p2 = is_const_v<double>;
	return 0;
}
