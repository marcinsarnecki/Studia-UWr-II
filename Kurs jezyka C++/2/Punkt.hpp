#pragma once

class Punkt {
private:
	double x, y;
public:
	void setX(double);
	void setY(double);
	double getX();
	double getY();
	void obrot(Punkt, double);
	Punkt operator-(const Punkt& a);
	void przesun(double, double);
	Punkt();
	Punkt(const Punkt&);
	Punkt(double, double);
};