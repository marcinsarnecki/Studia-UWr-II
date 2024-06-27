#include "tab_bit.hpp"

int main() {
	obliczenia::tab_bit dluga(100);
	dluga[50] = 1;
	dluga[80] = 1;
	std::cout << dluga << "\n";

	obliczenia::tab_bit b1(16);
	std::cout << "Tworze pusta tablice bitow wielkosci 16\n" << b1 << "\n";
	
	std::cout << "Zmieniam kilka bitow\n";
	b1[0] = 1;
	b1[3] = 1;
	b1[5] = 1;
	b1[10] = 1;
	b1[13] = 1;

	std::cout << b1 << "\n\n";

	std::cout << "Tworze druga tablice bitow wielkosci 16\n";
	obliczenia::tab_bit b2(b1);
	b2[5] = 0;
	b2[7] = 1;
	b2[10] = 0;
	b2[11] = 1;
	b2[3] = 0;
	b2[14] = 1;
	std::cout << b2 << "\n\n";

	std::cout << "Operacje bitowe:\n\n";
	std::cout	
		<< b1 << "\n"
		<< b2 << " OR\n"
		<< "----------------\n" 
		<< (b1 | b2) << "\n\n";

	std::cout 
		<< b1 << "\n"
		<< b2 << " AND\n"
		<< "----------------\n"
		<< (b1 & b2) << "\n\n";

	std::cout
		<< b1 << "\n"
		<< b2 << " XOR\n"
		<< "----------------\n"
		<< (b1 ^ b2) << "\n\n";

	std::cout
		<< b1 << " NOT\n"
		<< "----------------\n"
		<< (!b1) << "\n\n";

	std::cout << "Tworze trzecia tablice bitow uzywajac konstruktora przenoszacego druga tablice\n";
	obliczenia::tab_bit b3 = std::move(b2);
	std::cout << "Tablice 2: " << b2 << "\n";
	std::cout << "Tablica 3: " << b3 << "\n\n";

	std::cout << "Uzywam operatora = przenoszacego (b2 = b3)\n";
	b2 = std::move(b3);
	std::cout << "Tablice 2: " << b2 << "\n";
	std::cout << "Tablica 3: " << b3 << "\n\n";

	std::cout << "Sprobuje odwolac sie do indeksu spoza tablicy\n";
	try {
		std::cout << b1[100] << "\n\n";
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n\n";
	}

	std::cout << "Sprobuje wpisac nowa tablice\n";
	obliczenia::tab_bit b4;
	try {
		std::cin >> b4;
		std::cout << b4 << "\n";
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}

	obliczenia::tab_bit u(45ull);
	return 0;
}