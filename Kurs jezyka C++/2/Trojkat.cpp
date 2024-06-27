#include "Trojkat.hpp"
#include "Funkcje.hpp"
#include <iostream>

double Trojkat::obwod() {
	return odleglosc(p1, p2) + odleglosc(p2, p3) + odleglosc(p3, p1);
}
double Trojkat::pole() {
	return 0.5 * fabs((p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX()));
}
void Trojkat::przesun(double dx, double dy) {
	p1.setX(p1.getX() + dx);
	p1.setY(p1.getY() + dy);
	p2.setX(p2.getX() + dx);
	p2.setY(p2.getY() + dy);
	p3.setX(p3.getX() + dx);
	p3.setY(p3.getY() + dy);
}
void Trojkat::obrot(Punkt o, double alfa) {
	Punkt nowy1 = rotacja(p1, o, alfa);
	Punkt nowy2 = rotacja(p2, o, alfa);
	Punkt nowy3 = rotacja(p3, o, alfa);
	p1 = nowy1;
	p2 = nowy2;
	p3 = nowy3;
}
bool Trojkat::czyWewnatrz(Punkt a) {
	double	a1 = iloczyn(p1, p2, a),
		a2 = iloczyn(p2, p3, a),
		a3 = iloczyn(p3, p1, a);
	if (a1 >= 0 && a2 >= 0 && a3 >= 0)
		return true;
	if (a1 <= 0 && a2 <= 0 && a3 <= 0)
		return true;
	return false;
}
Punkt Trojkat::srodek() {
	return Punkt((p1.getX() + p2.getX() + p3.getX()) / 3.0, (p1.getY() + p2.getY() + p3.getY()) / 3.0);
}
void Trojkat::setP1(Punkt p) {
	p1 = p;
}
void Trojkat::setP2(Punkt p) {
	p2 = p;
}
void Trojkat::setP3(Punkt p) {
	p3 = p;
}
Punkt Trojkat::getP1() {
	return p1;
}
Punkt Trojkat::getP2() {
	return p2;
}
Punkt Trojkat::getP3() {
	return p3;
}
Trojkat::Trojkat(Punkt a, Punkt b, Punkt c) {
	if (czyRownolegle(Odcinek(a, b), Odcinek(b, c)))
		throw std::invalid_argument("Punkty trojkata leza na jednej prostej!");
	p1 = a;
	p2 = b;
	p3 = c;
}
Trojkat::Trojkat(const Trojkat& t1) {
	p1 = Punkt(t1.p1);
	p2 = Punkt(t1.p2);
	p3 = Punkt(t1.p3);
}
Trojkat::Trojkat() {
	p1 = p2 = p3 = Punkt();
}