#include <iostream>
#include "wymierna.hpp"

int main() {
	obliczenia::wymierna a(5);		// 5
	obliczenia::wymierna b(2, 9);	// 0.(2)
	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << a + b << "\n";
	std::cout << a - b << "\n";
	std::cout << a * b << "\n";
	std::cout << a / b << "\n";
	
	obliczenia::wymierna c(4, 8);	// 0.5
	std::cout << c << "\n";

	obliczenia::wymierna d = b + c;
	std::cout << d << "\n"; // 0.7(2)

	double dd = (double)d;
	std::cout << dd << "\n";
	int id = (int)d;
	std::cout << id << "\n";


	obliczenia::wymierna e = !a; 
	std::cout << e << "\n"; // 1/a = 0.2

	try {
		obliczenia::wymierna f(1, 0);
	}
	catch (obliczenia::dzielenie_przez_0 err) {
		std::cout << "Dzielenie przez 0\n";
	}

	try {
		obliczenia::wymierna big1(1000000, 1);
		obliczenia::wymierna big2(1000000, 1);
		obliczenia::wymierna x = big1 * big2;
	}
	catch (obliczenia::przekroczenie_zakresu err) {
		std::cout << "Przekroczony zakres\n";
	}


	return 0;
}