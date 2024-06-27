#include <iostream>
#include "wielomian.hpp"
#include <vector>



int main() {
	Wielomian w1({ 3,1,2 });
	Wielomian w2({ 2,2,3 });
	std::cout << "w1(x) = " << w1;
	std::cout << "w2(x) = " << w2;
	std::cout << "w1(3) = " << w1(3) << "\n";
	std::cout << "w1(4) = " << w1(4) << "\n";
	std::cout << "w1(5) = " << w1(5) << "\n";
	
	Wielomian w3(2,0);
	w3 -= w1;
	std::cout << "w1(x) - w2(x) = " << w3;

	return 0;
}