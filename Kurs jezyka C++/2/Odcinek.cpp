#include "Odcinek.hpp"
#include "Punkt.hpp"
#include "Funkcje.hpp"
#include <iostream>

void Odcinek::przesun(double dx, double dy) {
	p1.setX(p1.getX() + dx);
	p1.setY(p1.getY() + dy);
	p2.setX(p2.getX() + dx);
	p2.setY(p2.getY() + dy);
}
void Odcinek::obrot(Punkt o, double alfa) {
	Punkt nowy1 = rotacja(p1, o, alfa);
	Punkt nowy2 = rotacja(p2, o, alfa);
	p1 = nowy1;
	p2 = nowy2;
}
Punkt Odcinek::srodek() {
	return Punkt((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2);
}
Odcinek::Odcinek(Punkt a, Punkt b) {
	if (a.getX() == b.getX() && a.getY() == b.getY())
		throw std::invalid_argument("Punkty odcinka sa takie same!");
	p1 = a;
	p2 = b;
}
Odcinek::Odcinek(const Odcinek& o1) {
	p1 = Punkt(o1.p1);
	p2 = Punkt(o1.p2);
}
Odcinek::Odcinek() {
	p1 = p2 = Punkt();
}
void Odcinek::setP1(Punkt p) {
	p1 = p;
}
void Odcinek::setP2(Punkt p) {
	p2 = p;
}
Punkt Odcinek::getP1() {
	return p1;
}
Punkt Odcinek::getP2() {
	return p2;
}
double Odcinek::dlugosc() {
	return odleglosc(p1, p2);
}
bool Odcinek::czyNaOdcinku(Punkt p3) {
	if (iloczyn(p1, p3, p2) == 0 && //czy iloczyny skalarne sie zgadzaja
		iloczyn(p2, p3, p1) == 0 &&
		std::min(p1.getX(), p2.getX()) <= p3.getX() && //jesli tak to znaczy, ze p1 p2 p3 sa wspolliniowe, trzeba jeszcze sprawdzic czy p3 jest pomiedzy p1,p2
		p3.getX() <= std::max(p1.getX(), p2.getX()) &&
		std::min(p1.getY(), p2.getY()) <= p3.getY() &&
		p3.getY() <= std::max(p1.getY(), p2.getY())) return true;
	return false;
}