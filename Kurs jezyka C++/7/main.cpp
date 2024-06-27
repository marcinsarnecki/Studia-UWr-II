#include <iostream>
#include "tab_dbl.hpp"


int main() {
	std::cout << "Tworze pierwsza tablice i wypelniam kolejnymi liczbami\n";
	obliczenia::tab_dbl tab1(5);
	tab1[0] = 1;
	tab1[1] = 2;
	tab1[2] = 3;
	tab1[3] = 4;
	tab1[4] = 5;
	for (int i = 0; i < tab1.rozmiar(); i++)
		std::cout << tab1[i] << " ";
	std::cout << "\n\n";

	std::cout << "Tworze druga tablice i wypelniam losowymi liczbami\n";
	obliczenia::tab_dbl tab2(5);
	for (int i = 0; i < tab2.rozmiar(); i++)
		tab2[i] = obliczenia::tab_dbl::randomNumber();
	for (int i = 0; i < tab2.rozmiar(); i++)
		std::cout << tab2[i] << " ";
	std::cout << "\n\n";

	double iloczyn = tab1 * tab2;
	std::cout << "Iloczyn skalarny tych tablic wynosi " << iloczyn << "\n";
	std::cout << "\n\n";

	std::cout << "Sprobujmy odwolac sie do nieistniejacego indeksu\n";
	try {
		std::cout << tab1[1000] << "\n";
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	try {
		std::cout << tab1[-1] << "\n";
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	std::cout << "\n\n";

	std::cout << "Tworze trzecia tablice i uzywam konstruktora kopiujacego pierwsza tablice\n";
	obliczenia::tab_dbl tab3(tab1);
	for (int i = 0; i < tab3.rozmiar(); i++)
		std::cout << tab3[i] << " ";
	std::cout << "\n\n";

	std::cout << "Tworze czwarta tablice i uzywam konstruktora przenoszacego trzecia tablice\n";
	obliczenia::tab_dbl tab4(std::move(tab3));
	for (int i = 0; i < tab4.rozmiar(); i++)
		std::cout << tab4[i] << " ";
	std::cout << "\n\n";

	std::cout << "Tworze piata tablice zwyklym konstruktorem, nastepnie uzywam przypisania kopiujacego druga tablice\n";
	obliczenia::tab_dbl tab5(20);
	tab5 = tab2;
	for (int i = 0; i < tab5.rozmiar(); i++)
		std::cout << tab5[i] << " ";
	std::cout << "\n\n";

	std::cout << "Tworze szosta tablice zwyklym konstruktorem, nastepnie uzywam przypisania przenoszacego piata tablice\n";
	obliczenia::tab_dbl tab6(15);
	tab6 = tab5;
	for (int i = 0; i < tab6.rozmiar(); i++)
		std::cout << tab6[i] << " ";
	std::cout << "\n\n";

	std::cout << "Sprobujmy stworzyc tablice o niedozwolonym rozmiarze\n";
	try {
		obliczenia::tab_dbl tab7(-10);
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	std::cout << "\n\n";

	std::cout << "Tablica o maksymalnym rozmiarze\n";
	obliczenia::tab_dbl tab8;
	std::cout << "rozmiar = " << tab8.rozmiar() << "\n";

	obliczenia::tab_dbl tab10{ 1,2,3,4,5 };
	for (int i = 0; i < tab10.rozmiar(); i++)
		std::cout << tab10[i] << " ";


	return 0;
}