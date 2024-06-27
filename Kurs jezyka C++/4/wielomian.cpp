#include "wielomian.hpp"
#include<cmath>
#include<algorithm>

int Wielomian::stopien() {
	return n;
}

Wielomian::Wielomian(int stopien, double wspolczynnik) {
	n = stopien;
	a = new double[n + 1];
	for (int i = 0; i <= n; i++)
		a[i] = wspolczynnik;
}

Wielomian::Wielomian(std::initializer_list<double> l) {
	n = l.size()-1;
	a = new double[n + 1];
	int i = 0;
	for (auto it : l)
		a[i++] = it;
	std::reverse(a, a + n + 1);
}

Wielomian::Wielomian(const Wielomian& w)
{
	n = w.n;
	a = new double[n + 1];
	std::copy(w.a, w.a + w.n + 1, a);
}

Wielomian::Wielomian(Wielomian&& w)
{
	n = w.n;
	a = w.a;
	w.a = nullptr;
	w.n = 0;
}

Wielomian& Wielomian::operator = (const Wielomian& w)
{
	if (&w == this)
		return *this;
	this->~Wielomian();
	n = w.n;
	a = new double[n + 1];
	std::copy(w.a, w.a + w.n + 1, a);
	return *this;
}

Wielomian& Wielomian::operator = (Wielomian&& w)
{
	if (&w == this)
		return *this;
	this->~Wielomian();
	n = w.n;
	a = w.a;
	w.a = nullptr;
	w.n = 0;
	return *this;
}

Wielomian::~Wielomian()
{
	delete[] a;
}

Wielomian operator+(const Wielomian& w1, const Wielomian& w2) {
	Wielomian* w3 = new Wielomian(std::max(w1.n, w2.n),0);
	for (int i = 0; i <= w3->n; i++) {
		w3->a[i] = 0.0;
		if (i <= w1.n) w3->a[i] += w1.a[i];
		if (i <= w2.n) w3->a[i] += w2.a[i];
	}
	return *w3;
}

Wielomian& Wielomian::operator+=(const Wielomian& w1) {
	int newSize = std::max(n, w1.n);
	double* newTab = new double[newSize];
	for (int i = 0; i <= newSize; i++) {
		newTab[i] = 0.0;
		if (i <= n) newTab[i] += a[i];
		if (i <= w1.n) newTab[i] += w1.a[i];
	}
	n = newSize;
	if (a) delete[]a;
	a = newTab;
	return *this;
}

Wielomian operator-(const Wielomian& w1, const Wielomian& w2) {
	Wielomian *w3 = new Wielomian(std::max(w1.n, w2.n),0);
	for (int i = 0; i <= w3->n; i++) {
		w3->a[i] = 0.0;
		if (i <= w1.n) w3->a[i] += w1.a[i];
		if (i <= w2.n) w3->a[i] -= w2.a[i];
	}
	return *w3;
}

Wielomian& Wielomian::operator-=(const Wielomian& w1) {
	int newSize = std::max(n, w1.n);
	double* newTab = new double[newSize];
	for (int i = 0; i <= newSize; i++) {
		newTab[i] = 0.0;
		if (i <= n) newTab[i] += a[i];
		if (i <= w1.n) newTab[i] -= w1.a[i];
	}
	n = newSize;
	if (a) delete[]a;
	a = newTab;
	return *this;
}

Wielomian operator*(const Wielomian& w1, const Wielomian& w2) {
	Wielomian w3(w1.n + w2.n,0);
	for (int i = 0; i <= w1.n; i++)
		for (int j = 0; j <= w2.n; j++)
			w3.a[i + j] += w1.a[i] * w2.a[j];
	return w3;
}

Wielomian& Wielomian::operator*=(const Wielomian& w1) {
	int newSize = std::max(n, w1.n);
	double* newTab = new double[newSize];
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= w1.n; j++)
			a[i + j] += a[i] * w1.a[j];
	n = newSize;
	if (a) delete[]a;
	a = newTab;
	return *this;
}

Wielomian operator*(const Wielomian& w1, double c) {
	Wielomian w2(w1.n,0);
	for (int i = 0; i <= w2.n; i++) {
		w2.a[i] = w1.a[i] * c;
	}
	return w2;
}

double Wielomian::operator()(double x) const{
	double ans = 0.0;
	for (int i = 0; i <= n; i++)
		ans +=  a[i] * pow(x, i);
	return ans;
}

double Wielomian::operator[](int i) const {
	return a[i];
}

std::istream& operator>>(std::istream& In, Wielomian& w1)
{
	std::cout << "Wpisz stopien: ";
	In >> w1.n;
	std::cout << "Wpisz wspolczynniki: \n";
	if (w1.a) delete[] w1.a;
	w1.a = new double[w1.n + 1];
	for (int i = 0; i < w1.n + 1; ++i) In >> w1.a[i];
	return In;
}

std::ostream& operator<<(std::ostream& Out, const Wielomian& w1)
{
	bool b = 1;
	for (int i = w1.n; i >= 0; i--) {
		if (w1.a[i] != 0) {
			if (!b) {
				if (w1.a[i] > 0) Out << " + ";
				if (w1.a[i] < 0) Out << " - ";
			}
			if(fabs(w1.a[i]) != 1.0 || i == 0) Out << fabs(w1.a[i]);
			if (i > 0) std::cout << 'x';
			if (i > 1) Out << "^" << i;
			b = 0;
		}
	}
	std::cout << "\n";
	return Out;
}

Wielomian::Wielomian() {
	n = 0;
	a = nullptr;
}