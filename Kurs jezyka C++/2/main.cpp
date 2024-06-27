#include <iostream>
#include <stdexcept>
#include "Punkt.hpp"
#include "Odcinek.hpp"
#include "Funkcje.hpp"
#include "Trojkat.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>


int main() {
	//std::cout << std::fixed << std::setprecision(2);
	Punkt p(4.0, 3.0);
	std::cout << "Stworzylem punkt (p) o wspolrzednych (" << p.getX() << "," << p.getY() << ")\n";
	std::cout << "Przesuwam punkt (p) o wektor (1,2)\n";
	p.przesun(1.0, 2.0);
	std::cout << "Wspolrzedne punktu (p): (" << p.getX() << "," << p.getY() << ")\n\n";

	std::cout << "Obracam (p) wzgledem (10,5) o 90 stopni!\n";
	p.obrot(Punkt(10.0, 5.0), M_PI / 2);
	std::cout << "Wspolrzedne punktu (p): (" << p.getX() << "," << p.getY() << ")\n\n";
	std::cout << "Obracam (p) wzgledem (10,5) o 90 stopni!\n";
	p.obrot(Punkt(10.0, 5.0), M_PI / 2);
	std::cout << "Wspolrzedne punktu (p): (" << p.getX() << "," << p.getY() << ")\n\n";
	std::cout << "Obracam (p) wzgledem (10,5) o 90 stopni!\n";
	p.obrot(Punkt(10.0, 5.0), M_PI / 2);
	std::cout << "Wspolrzedne punktu (p): (" << p.getX() << "," << p.getY() << ")\n\n";
	std::cout << "Obracam (p) wzgledem (10,5) o 90 stopni!\n";
	p.obrot(Punkt(10.0, 5.0), M_PI / 2);
	std::cout << "Wspolrzedne punktu (p): (" << p.getX() << "," << p.getY() << ")\n";
	std::cout << "Po 4 obrotach o 90 stopni wrocilem do punktu wyjscia!\n\n\n";

	Punkt q(p);
	q.przesun(4.0, 3.0);
	std::cout << "Tworze punkt (q), nadaje mu wartosc punktu (p), po czym przesuwam o wektor (4,3)\n";
	std::cout << "(q): (" << q.getX() << "," << q.getY() << ")\n\n";
	Odcinek A, B;
	try {
		Odcinek Aa(p, q);
		A = Odcinek(Aa);
		std::cout << "Stworzylem odcinek A miedzy punktami (p) oraz (q), jego dlugosc wynosi "<<A.dlugosc()<<"\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Odcinek nie moze miec dlugosci 0\n";
	}

	try {
		Odcinek Bb(p, p);
		std::cout << "Probuje stworzyc odcinek o zerowej dlugosci\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Odcinek nie moze miec dlugosci 0\n\n";
	}

	try {
		Odcinek Bb(Punkt(5.0,8.0), Punkt(9.0,5.0));
		B = Odcinek(Bb);
		std::cout << "Tworze odcinek B miedzy punktami (5,8) i (9,5)\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Odcinek nie moze miec dlugosci 0\n";
	}

	try {
		std::cout << "Sprawdzmy, w ktorym miejscu odcinki A i B sie przecinaja\n";
		Punkt r = punktPrzeciecia(A, B);
		std::cout << "Odcinki przecinaja sie w punkcie (" << r.getX() << "," << r.getY() << ")\n";
		std::cout << "Sprawdzmy, czy ten punkt lezy w obu odcinkach\n";
		if (A.czyNaOdcinku(r) && B.czyNaOdcinku(r))
			std::cout << "Tak, zgadza sie\n\n";
		else
			std::cout << "Nie, punkt zostal zle wyliczony!\n\n";

	}
	catch (std::invalid_argument arg) {
		std::cout << "Odcinki nie maja punktu wspolnego!\n";
	}

	try {
		Odcinek o1(Punkt(1,1), Punkt(3,1)), o2(Punkt(1,3), Punkt(4,3));
		std::cout << "Sprawdzmy, czy odcinki (1,1)-(3,1) oraz (1,3)-(4,3) maja punkt wspolny\n";
		Punkt r = punktPrzeciecia(o1, o2);
		std::cout << "Odcinki przecinaja sie w punkcie " << r.getX() << " " << r.getY() << "\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Odcinki nie maja punktu wspolnego!\n\n";
	}

	std::cout << "Stworzmy trojkat t1 o punktach (2,2), (8,2), (2,7)\n";
	Trojkat t1;
	try {
		t1 = Trojkat(Punkt(2.0, 2.0), Punkt(8.0, 2.0), Punkt(2.0, 7.0));
		std::cout << "Punkty sa poprawne! (nie leza na jednej linii)\n";
		std::cout << "Jego pole wynosi " << t1.pole() << ", a obwod jest rowny " << t1.obwod() << "\n";
		std::cout << "Srodek znajduje sie w punkcie (" << t1.srodek().getX() << "," << t1.srodek().getY() << ")\n";
		std::cout << "Obracam trojkat wzgledem punktu (0,0) o 180 stopni!\n";
		t1.obrot(Punkt(0, 0), M_PI);
		std::cout << "Teraz jego punkty sa rowne (" << t1.getP1().getX() << "," << t1.getP1().getY() << ") ("
			<< t1.getP2().getX() << "," << t1.getP2().getY() << ") ("
			<< t1.getP3().getX() << "," << t1.getP3().getY() << ")\n\n";
		t1.obrot(Punkt(0, 0), M_PI);
		std::cout << "Obracam z powrotem! Punkty: (" << t1.getP1().getX() << "," << t1.getP1().getY() << ") ("
			<< t1.getP2().getX() << "," << t1.getP2().getY() << ") ("
			<< t1.getP3().getX() << "," << t1.getP3().getY() << ")\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Punkty leza na jednej linii!\n\n";
	}

	std::cout << "Stworzmy trojkat o punktach (0,0), (1,1), (2,2)\n";//zly trojkat
	Trojkat t2;
	try {
		t2 = Trojkat(Punkt(0,0), Punkt(1,1), Punkt(2,2));
		std::cout << "Punkty sa poprawne! (nie leza na jednej linii)\n";
		std::cout << "Jego pole wynosi " << t2.pole() << ", a obwod jest rowny " << t2.obwod() << "\n";
		std::cout << "Srodek znajduje sie w punkcie (" << t2.srodek().getX() << "," << t2.srodek().getY() << ")\n";
		std::cout << "Obracam trojkat wzgledem punktu (0,0) o 180 stopni!\n";
		t2.obrot(Punkt(0, 0), M_PI);
		std::cout << "Teraz jego punkty sa rowne (" << t2.getP1().getX() << "," << t2.getP1().getY() << ") ("
			<< t2.getP2().getX() << "," << t2.getP2().getY() << ") ("
			<< t2.getP3().getX() << "," << t2.getP3().getY() << ")\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Punkty leza na jednej linii!\n\n";
	}



	//odcinki prostopadle
	Odcinek o1(Punkt(0,0), Punkt(10, 1)), o2(Punkt(0, 0), Punkt(1, -10));
	std::cout << "Sprawdzmy, czy odcinki (0,0)-(10,1) oraz (0,0)-(1,-10) sa prostopadle\n";
	if (czyProstopadle(o1, o2))
		std::cout << "Tak, sa prostopadle\n\n";
	else std::cout << "Nie, nie sa prostopadle\n\n";

	//rownolegle
	o1 = Odcinek(Punkt(0, 0), Punkt(100, 0)), o2 = Odcinek(Punkt(0, 0), Punkt(100, 0.1));
	std::cout << "Sprawdzmy, czy odcinki (0,0)-(100,1) oraz (0,0)-(100,0.1) sa rownolegle\n";
	if (czyRownolegle(o1, o2))
		std::cout << "Tak, sa rownolegle\n\n";
	else std::cout << "Nie, nie sa rownolegle\n\n";
	
	std::cout << "Stworzmy trojkat t2 o punktach (0,0), (10,0), (3,13)\n";//duzy, zeby sie zawieraly w sobie
	try {
		t2 = Trojkat(Punkt(0.0, 0.0), Punkt(10.0, 0.0), Punkt(3.0, 13.0));
		std::cout << "Punkty sa poprawne! (nie leza na jednej linii)\n";
		std::cout << "Jego pole wynosi " << t2.pole() << ", a obwod jest rowny " << t2.obwod() << "\n";
		std::cout << "Sprawdzmy, czy jeden zawiera drugi (t1 i t2)\n";
		if (czyTrojkatySieZawieraja(t1, t2))
			std::cout << "Tak, jeden z nich calkowicie zawiera sie w drugim\n\n";
		else std::cout << "Nie, zaden z nich nie zawiera sie w drugim\n\n";
	}
	catch (std::invalid_argument arg) {
		std::cout << "Punkty leza na jednej linii!\n\n";
	}

	std::cout << "Przesuwam t1 o wektor (6,0)\n\n";
	t1.przesun(6, 0);

	std::cout << "Sprawdzam, czy trojkaty t1 i t2 sa rozlaczne\n";
	std::cout << "t1: (" << t1.getP1().getX() << "," << t1.getP1().getY() << ") ("
		<< t1.getP2().getX() << "," << t1.getP2().getY() << ") ("
		<< t1.getP3().getX() << "," << t1.getP3().getY() << ")\n";
	std::cout << "t2: (" << t2.getP1().getX() << "," << t2.getP1().getY() << ") ("
		<< t2.getP2().getX() << "," << t2.getP2().getY() << ") ("
		<< t2.getP3().getX() << "," << t2.getP3().getY() << ")\n";
	if (czyTrojkatySaRozlaczne(t1, t2))
		std::cout << "Sa rozlaczne!\n";
	else std::cout << "Nie sa rozlaczne!\n";

	std::cout << "Odrobine przesuwam jeden z punktow t1\n";
	t1.setP1(Punkt(t1.getP1().getX() + 1, t1.getP1().getY()));
	std::cout << "t1: (" << t1.getP1().getX() << "," << t1.getP1().getY() << ") ("
		<< t1.getP2().getX() << "," << t1.getP2().getY() << ") ("
		<< t1.getP3().getX() << "," << t1.getP3().getY() << ")\n";
	if (czyTrojkatySaRozlaczne(t1, t2))
		std::cout << "Sa rozlaczne!\n";
	else std::cout << "Nie sa rozlaczne!\n";
	return 0;
}