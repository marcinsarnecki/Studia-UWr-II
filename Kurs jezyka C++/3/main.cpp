#include<iostream>
#include "kolejka.hpp"

int main() {
	int z = 0;
	std::string input;
	kolejka q1(5);

	while (z != 7) {
		std::cout << "Podaj operacje na kolejce\n";
		std::cout << "1: Dodaj element do kolejki\n";
		std::cout << "2: Usun element\n";
		std::cout << "3: Wyswietl pierwszy element kolejki\n";
		std::cout << "4: Sprawdz aktualny rozmiar\n";
		std::cout << "5: Sprawdz pojemnosc\n";
		std::cout << "6: Wyswietl cala kolejke\n";
		std::cout << "7: Zakoncz interakcje\n";
		std::cin >> z;
		std::getchar();
		switch (z) {
		case 1:
			system("CLS");
			std::cout << "Wpisz: ";
			std::getline(std::cin, input);
			q1.wloz(input);
			break;
		case 2:
			system("CLS");
			std::cout<<"Usunieto element \""<<q1.wyciagnij()<<"\"\n";
			break;
		case 3:
			system("CLS");
			std::cout << "Pierwszy element: \"" << q1.naprzodzie() << "\"\n";
			break;
		case 4:
			system("CLS");
			std::cout << "Aktualny rozmiar wynosi " << q1.rozmiar() << "\n";
			break;
		case 5:
			system("CLS");
			std::cout << "Pojemnosc wynosi " << q1.pojemnosc() << "\n";
			break;
		case 6:
			system("CLS");
			std::cout << "Cala kolejka:\n";
			q1.wypisz();
			break;
		case 7:
			system("CLS");
			break;
		default:
			system("CLS");
			std::cout << "Wpisana liczba jest spoza zakresu 1-7\n";
			break;
		}
		std::cout << "\n";
	}
	std::cout << "Testuje konstruktor kopiujacy! Tworze druga kolejke i kopiuje zawartosc pierwszej\n\n";
	kolejka q2(q1);

	std::cout << "Teraz rozmiar kolejki pierwszej wynosi " << q1.rozmiar() << ", wyswietlam wszystkie elementy:\n";
	q1.wypisz();
	std::cout << "\n";

	std::cout << "Teraz rozmiar kolejki drugiej wynosi " << q2.rozmiar() << ", wyswietlam wszystkie elementy:\n";
	q2.wypisz();
	std::cout << "\n";

	std::cout << "Testuje konstruktor przenoszacy! Tworze trzecia kolejke i przenosze zawartosc drugiej\n\n";
	kolejka q3(std::move(q2));

	std::cout << "Teraz rozmiar kolejki drugiej wynosi " << q2.rozmiar() << ", wyswietlam wszystkie elementy:\n";
	q2.wypisz();
	std::cout << "\n";

	std::cout << "Teraz rozmiar kolejki trzeciej wynosi " << q3.rozmiar() << ", wyswietlam wszystkie elementy:\n";
	q3.wypisz();
	std::cout << "\n";

	return 0;
}