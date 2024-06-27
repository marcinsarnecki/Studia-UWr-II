#include "tab_dbl.hpp"

namespace obliczenia {
	tab_dbl::tab_dbl(int rozm) { //zwykly konstruktor z jednym argumentem
		if (rozm < 1)
			throw std::invalid_argument("Rozmiar nie moze byc mniejszy niz 1");
		this->dl = rozm;
		this->tab = new double[dl];
		for (int i = 0; i < dl; i++)
			this->tab[i] = 0.0;
	}

	tab_dbl::tab_dbl() {
		int size = (1 << 27);// 2^27 = 134217728, double ma 8 bajtow, wiec tablica zajmuje ponad 1gb, 2^28 nie przechodzi (limit 2gb)
		this->dl = size;
		this->tab = new (std::nothrow) double[this->dl];
		if (!this->tab) {  // jesli sie nie udalo to tab jest null pointerem traktowanym jako falsz
			std::cout << "Nie udalo sie!\n";
		}
		else {
			std::cout << "Udalo sie!\n";
			for (int i = 0; i < this->dl; i++)
				this->tab[i] = this->randomNumber();
			//for (int i = 0; i < this->dl; i++)
			//	std::cout << tab[i] << "\n";
		}
	}

	tab_dbl::tab_dbl(std::initializer_list<double> l) {
		this->tab = new double[l.size()];
		this->dl = l.size();
		int i = 0;
		for (auto it : l)
			this->tab[i++] = it;
	}

	tab_dbl::tab_dbl(const tab_dbl& t) {//kopiujacy
		this->dl = t.dl;
		this->tab = new double[dl];
		for (int i = 0; i < this->dl; i++)
			this->tab[i] = t.tab[i];
	}

	tab_dbl::tab_dbl(tab_dbl&& t) {//przenoszacy
		this->dl = t.dl;
		this->tab = t.tab;
		t.tab = nullptr;
	}

	tab_dbl& tab_dbl::operator=(const tab_dbl& t) {//przypisanie kopiujace
		if (&t == this)
			return *this;
		this->~tab_dbl();
		this->dl = t.dl;
		this->tab = new double[this->dl];
		for (int i = 0; i < this->dl; i++)
			this->tab[i] = t.tab[i];
		return *this;
	}

	tab_dbl& tab_dbl::operator=(tab_dbl&& t) {//przypisanie przenoszace
		if (&t == this)
			return *this;
		this->~tab_dbl();
		this->dl = t.dl;
		this->tab = t.tab;
		t.tab = nullptr;
		return *this;
	}

	tab_dbl::~tab_dbl() {
		delete[] tab;
	}

	double tab_dbl::operator[](int i) const
	{
		if (i < 0 || i >= this->dl)
			throw std::exception("out of range");
		return this->tab[i];
	}

	double& tab_dbl::operator[](int i)
	{
		if (i < 0 || i >= this->dl)
			throw std::exception("out of range");
		return this->tab[i];
	}

	double tab_dbl::randomNumber() {
		return (double)rand() / ((double)RAND_MAX + 1);
	}

	int tab_dbl::rozmiar() {
		return this->dl;
	}

	double operator*(const tab_dbl& tab1, const tab_dbl& tab2)
	{
		assert(tab1.dl == tab2.dl);
		double ans = 0.0;
		for (int i = 0; i < tab1.dl; i++)
			ans += tab1[i] * tab2[i];
		return ans;
	}
}