#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <set>

template <typename T>
struct Test {
	T a;
	T b;
	T c;
};

int main() {
	Test<int> t{ 1,2,3 };
	Test<double> d{ .a = 2,.b = 3,.c = 4 };
	Test<std::string> d{ .a = "2",.b = "3",.c = "4"};
	return 0;
}
