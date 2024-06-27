#pragma once
#include "Punkt.hpp"

class Trojkat {
private:
	Punkt p1, p2, p3;
public:
	void setP1(Punkt);
	void setP2(Punkt);
	void setP3(Punkt);
	Punkt getP1();
	Punkt getP2();
	Punkt getP3();
	void przesun(double, double);
	void obrot(Punkt, double);
	double obwod();
	double pole();
	Punkt srodek();
	bool czyWewnatrz(Punkt);
	Trojkat(Punkt, Punkt, Punkt);
	Trojkat(const Trojkat&);
	Trojkat();
};