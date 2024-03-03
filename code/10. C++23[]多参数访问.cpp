#include <iostream>


/*
C++23 + GCC编译器可通过
*/

struct Node {
	template <typename...Args>
	void operator[](Args&&...args) {
		((std::cout << args << ' '), ...);
		std::cout << '\n';
	}
};
int main() {
	Node node;
	// node[1, 2.1, 'a', "dawdad"];
	int a[2][2]{ 1,2,3,4 };
	//std::cout << *a[1, 1] << '\n';

	return 0;
}
