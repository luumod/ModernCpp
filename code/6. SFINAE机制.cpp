#include <iostream>

template <typename T>
struct B {
	using type = typename T::type;

	int a;
};

template <typename T,
		  typename U = typename T::type,
		  typename V = typename B<T>::type>
void foo(int) {
	std::cout << "SFINAE\n";
}

template <typename T>
void foo(double) {
	std::cout << "Normal\n";
}


template<typename T>
// C++11 后置返回类型，在返回类型中运用 SFINAE
auto add(const T& t1, const T& t2)->decltype(t1 + t2) {   
	std::puts("SFINAE +");
	return t1 + t2;
}

template <typename T>
struct Test {
	Test() {}
	Test(int a) :a(a) {}

	using type = T;
	int a;
	void f()const {}
	int operator+(const Test& tmp) const{
		return this->a + tmp.a;
	}
};

template <typename Type, typename...Args>
Test(Type, Args...) -> Test < std::enable_if_t< (std::is_same_v<Type, Args> && ...), Type>>;

/*
1. typename SFINAE = std::void_t<decltype(T{} + T{}) >
2. ->decltype( a + b)
*/
template <typename T, typename SFINAE = std::void_t<
	decltype(T{} + T{}), //必须有重载+运算符 且 默认构造函数
	typename T::type,	 //必须有type类型别名
	decltype(&T::f),	 //必须有f成员函数
	decltype(&T::a) >>	 //必须有a成员变量
auto addd(const T& a, const T& b){
	std::cout << "SFINAE\n";
	return a + b;
}

//--------------------------
//template<typename T, typename SFINAE = std::void_t<decltype(T{} + T{}) > >
//auto adddd(const T& t1, const T& t2) {
//	std::puts("SFINAE +");
//	return t1 + t2;
//}

// declval: 将任意类型 T 转换成引用类型，使得在 decltype 说明符的操作数中不必经过构造函数就能使用成员函数。
template<typename T, typename SFINAE = std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
auto adddd(const T& t1, const T& t2) {
	std::puts("SFINAE +");
	return t1 + t2;
}

struct X {
	X() {}
	int operator+(const X&)const {
		return 0;
	}
};

struct X2 {
	X2(int) {} 
	int operator+(const X2&)const {
		return 0;
	}
};

int main() {
	struct C { using type = int; };

	foo<B<C>>(1);	 //SFINAE
	foo<C>(1);		 //SFINAE
	foo<int>(1);

	//----------------------
	Test a{111};
	Test b{ 222 };
	auto c  = addd(a , b);
	std::cout << c << '\n';

	//----------------------
	X x1, x2;
	adddd(x1, x2);          // OK

	X2 x3{ 0 }, x4{ 0 };
	adddd(x3, x4);           // 未找到匹配的重载函数

	return 0;
}