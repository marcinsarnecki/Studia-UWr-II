#include "wyrazenia.hpp"

int main() {
	wyrazenie* w1 = new dziel( // (x-1)*x/2
		new mnoz(
			new odejmij(
				new zmienna("x"),
				new liczba(1)
			),
			new zmienna("x")
		),
		new liczba(2)
	);
	wyrazenie* w2 = new dziel( //(3+5)/(2+x*7)
		new dodaj(
			new liczba(3), 
			new liczba(5)
		),
		new dodaj(
			new liczba(2),
			new mnoz(
				new zmienna("x"), 
				new liczba(7)
			)
		)
	);
	wyrazenie* w3 = new odejmij( //2+x*7-(y*3+5)
		new dodaj(
			new liczba(2),
			new mnoz(
				new zmienna("x"),
				new liczba(7)
			)
		),
		new dodaj(
			new mnoz(
				new zmienna("y"), 
				new liczba(3)),
			new liczba(5)
		)
	);
	wyrazenie* w4 = new dziel( //cos((x+1)*x)/e^x^2
		new cosinus(new mnoz(
			new dodaj(
				new zmienna("x"),
				new liczba(1)),
			new zmienna("x")
			)
		),
		new potega(
			new potega(new e(),new zmienna("x")),
			new liczba(2))

	);
	std::cout << w1->zapis() << "\n";
	std::cout << w2->zapis() << "\n";
	std::cout << w3->zapis() << "\n";
	std::cout << w4->zapis() << "\n";
	zmienna::dodajZmienna("y", 0);
	zmienna::dodajZmienna("x", 0);
	for (double x = 0; x <= 1.0; x += 0.01) {
		zmienna::zmodyfikujZmienna("x", x);
		std::cout << " " << w1->oblicz() << " " << w2->oblicz() << " " << w3->oblicz() << " " << w4->oblicz() << "\n";
	}

	return 0;
}