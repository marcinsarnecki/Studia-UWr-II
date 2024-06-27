#include "Funkcje.hpp"
#include "Trojkat.hpp"
#include <algorithm>
#include <iostream>

double odleglosc(Punkt p1, Punkt p2) {
	return sqrtl(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

double iloczyn(Punkt p1, Punkt p2, Punkt p3) {
	//std::cout << "iloczyn z punktow (" << p1.getX() << "," << p1.getY() << ") (" << p2.getX() << "," << p2.getY() << ") (" << p3.getX() << "," << p3.getY() << ")  wynosi " << (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p3.getX() - p1.getX()) * (p2.getY() - p1.getY())<<"\n";
	return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p3.getX() - p1.getX()) * (p2.getY() - p1.getY());
}

bool czyProstopadle(Odcinek o1, Odcinek o2) {
	double alfa = iloczyn(Punkt(0.0, 0.0), o1.getP2() - o1.getP1(), o2.getP2() - o2.getP1()) / (o1.dlugosc() * o2.dlugosc());
	if (alfa == 1.0 || alfa == -1.0) return true;
	return false;
}

bool czyRownolegle(Odcinek o1, Odcinek o2) {
	if (iloczyn(Punkt(0.0, 0.0), o1.getP2() - o1.getP1(), o2.getP2() - o2.getP1()) == 0.0) return true;
	return false;
}

bool czyTrojkatySieZawieraja(Trojkat t1, Trojkat t2) {
	if (t1.czyWewnatrz(t2.getP1()) && t1.czyWewnatrz(t2.getP2()) && t1.czyWewnatrz(t2.getP3()))
		return true;
	if (t2.czyWewnatrz(t1.getP1()) && t2.czyWewnatrz(t1.getP2()) && t2.czyWewnatrz(t1.getP3()))
		return true;
	return false;
}

bool czyPrzecinajaSie(Odcinek o1, Odcinek o2) {
	Punkt p1 = Punkt(o1.getP1()),
		p2 = Punkt(o1.getP2()),
		p3 = Punkt(o2.getP1()),
		p4 = Punkt(o2.getP2());
	double d1 = iloczyn(p3, p4, p1),
		d2 = iloczyn(p3, p4, p2),
		d3 = iloczyn(p1, p2, p3),
		d4 = iloczyn(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;
	else if (d1 == 0 && o2.czyNaOdcinku(o1.getP1()))
		return true;
	else if (d2 == 0 && o2.czyNaOdcinku(o1.getP2()))
		return true;
	else if (d3 == 0 && o1.czyNaOdcinku(o1.getP1()))
		return true;
	else if (d4 == 0 && o1.czyNaOdcinku(o1.getP2()))
		return true;
	else return false;
}

Punkt punktPrzeciecia(Odcinek o1, Odcinek o2) {
	if (!czyPrzecinajaSie(o1, o2)) 
		throw std::invalid_argument("Odcinki nie maja punktu wspolnego!");
	Odcinek ox(Punkt(0, 0), Punkt(1, 0));
	if (czyProstopadle(o1, ox) && czyProstopadle(o2, ox)) //oba pionowe i rownolegle
		return Punkt(o1.getP1().getX(), std::max(std::min(o1.getP1().getY(), o1.getP2().getY()), std::min(o2.getP1().getY(), o2.getP2().getY())));
	if (czyRownolegle(o1, ox) && czyRownolegle(o2, ox)) //oba poziome i rownolegle
		return Punkt(std::max(std::min(o1.getP1().getX(), o1.getP2().getX()), std::min(o2.getP1().getX(), o2.getP2().getX())), o1.getP1().getY());
	if (czyProstopadle(o2, ox)) {//jesli jeden z nich jest pionowy to wtedy jest nim o1
		std::swap(o1, o2);
		double a2 = (o2.getP2().getY() - o2.getP1().getY()) / (o2.getP2().getX() - o2.getP1().getX());
		double b2 = o2.getP1().getY() - a2 * o2.getP1().getX();
		/*std::cout << a2 << " " << b2 << " a2 b2\n";*/
		return Punkt(o1.getP1().getX(), a2 * o1.getP1().getX() + b2);
	}
	double a2 = (o2.getP2().getY() - o2.getP1().getY()) / (o2.getP2().getX() - o2.getP1().getX());
	double b2 = o2.getP1().getY() - a2 * o2.getP1().getX();
	double a1 = (o1.getP2().getY() - o1.getP1().getY()) / (o1.getP2().getX() - o1.getP1().getX());
	double b1 = o1.getP1().getY() - a1 * o1.getP1().getX();
	/*std::cout << a1 << " " << b1 << " a1 b1\n";
	std::cout << a2 << " " << b2 << " a2 b2\n";*/
	return Punkt((b2 - b1) / (a1 - a2), a1 * (b2 - b1) / (a1 - a2) + b1);//XD
}

bool czyTrojkatySaRozlaczne(Trojkat t1, Trojkat t2) {
	if (czyTrojkatySieZawieraja(t1, t2) || czyTrojkatySieZawieraja(t2, t1))
		return false;
	if (czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP2()), Odcinek(t2.getP1(), t2.getP2())) ||
		czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP2()), Odcinek(t2.getP2(), t2.getP3())) ||
		czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP2()), Odcinek(t2.getP1(), t2.getP3())) ||
		czyPrzecinajaSie(Odcinek(t1.getP2(), t1.getP3()), Odcinek(t2.getP1(), t2.getP2())) ||
		czyPrzecinajaSie(Odcinek(t1.getP2(), t1.getP3()), Odcinek(t2.getP2(), t2.getP3())) ||
		czyPrzecinajaSie(Odcinek(t1.getP2(), t1.getP3()), Odcinek(t2.getP1(), t2.getP3())) ||
		czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP3()), Odcinek(t2.getP1(), t2.getP2())) ||
		czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP3()), Odcinek(t2.getP2(), t2.getP3())) ||
		czyPrzecinajaSie(Odcinek(t1.getP1(), t1.getP3()), Odcinek(t2.getP1(), t2.getP3()))
		)
		return false;
	return true;
}

Punkt rotacja(Punkt p, Punkt o, double alfa) {
	double s = sin(alfa);
	double c = cos(alfa);
	p.setX(p.getX() - o.getX());
	p.setY(p.getY() - o.getY());
	double x = p.getX() * c - p.getY() * s;
	double y = p.getX() * s + p.getY() * c;
	p.setX(x + o.getX());
	p.setY(y + o.getY());
	return p;
}