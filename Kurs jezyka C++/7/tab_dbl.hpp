#pragma once
#include <stdexcept>
#include <iostream>
#include <cassert>
namespace obliczenia {

	class tab_dbl
	{
		double* tab; // tablica liczb zmiennopozycyjnych
		int dl; // rozmiar tablicy
	public:
		explicit tab_dbl(int rozm); // wyzerowana tablica liczb
		tab_dbl();//default
		tab_dbl(std::initializer_list<double> l);
		tab_dbl(const tab_dbl& t); // konstruktor kopiuj¹cy
		tab_dbl(tab_dbl&& t); // konstruktor przenosz¹cy
		tab_dbl& operator = (const tab_dbl& t); // przypisanie kopiuj¹ce
		tab_dbl& operator = (tab_dbl&& t); // przypisanie przenosz¹ce
		~tab_dbl(); // destruktor
		double operator[](int i) const;
		double& operator[](int i);
		static double randomNumber();
		int rozmiar();
		friend double operator*(const tab_dbl& tab1, const tab_dbl& tab2);
	};

}