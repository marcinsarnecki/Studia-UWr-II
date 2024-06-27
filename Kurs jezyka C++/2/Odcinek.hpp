#pragma once
#include "Punkt.hpp"

class Odcinek {
	private:
		Punkt p1, p2;
	public:
		void setP1(Punkt);
		void setP2(Punkt);
		Punkt getP1();
		Punkt getP2();
		void przesun(double, double);
		void obrot(Punkt, double);
		double dlugosc();
		Punkt srodek();
		bool czyNaOdcinku(Punkt);
		Odcinek(Punkt, Punkt);
		Odcinek(const Odcinek&);
		Odcinek();
};