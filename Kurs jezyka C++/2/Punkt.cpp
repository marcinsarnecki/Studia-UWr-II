#include "Punkt.hpp"
#include "Funkcje.hpp"

Punkt::Punkt(double a, double b) {
	x = a;
	y = b;
}

void Punkt::obrot(Punkt o, double alfa) {
	Punkt nowy1 = rotacja(Punkt(x,y), o, alfa);
	x = nowy1.getX();
	y = nowy1.getY();
}

void Punkt::przesun(double dx, double dy) {
	x += dx;
	y += dy;
}

Punkt::Punkt() {
	x = y = 0.0;
}

Punkt::Punkt(const Punkt& p1) {
	x = p1.x;
	y = p1.y;
}

Punkt Punkt::operator-(const Punkt& a) {//taki po prostu operator na odejmowanie
	return Punkt(x - a.x, y - a.y);
}

void Punkt::setX(double num) {
	x = num;
}

void Punkt::setY(double num) {
	y = num;
}

double Punkt::getX() {
	return x;
}

double Punkt::getY() {
	return y;
}