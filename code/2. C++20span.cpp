#include <iostream>
#include <vector>
#include <span>

template <typename T>
void print(std::span<T> span)noexcept {
	for (const auto& x : span) {
		std::cout << x << " ";
	}
	std::cout << "span.size(): " << span.size() << '\n';
}
int main() {
	std::vector<int> v1{ 1,2,3,4,5 };
	std::vector<std::string> v2{ "111","222","333","444","555" };
	print<int>(v1);
	print<std::string>(v2);
	return 0;
}