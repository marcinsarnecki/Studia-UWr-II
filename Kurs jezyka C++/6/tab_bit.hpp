#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

namespace obliczenia {
	class tab_bit
	{
		typedef uint64_t slowo; // komorka w tablicy
		static const int rozmiarSlowa = 64; // rozmiar slowa w bitach
		friend std::istream& operator >> (std::istream& we, tab_bit& tb);
		friend std::ostream& operator << (std::ostream& wy, const tab_bit& tb);
		class ref {// klasa pomocnicza do adresowania bit�w
			int idx;
			slowo* ptr;
		public:
			ref(int i, slowo* s);//konstruktor zwykly
			ref& operator=(bool wartosc);//dany bit na konkretna wartosc
			ref& operator=(const ref& bit);//pojedynczy bit
			operator bool()const; //ref zostanie potraktowane jako bool 
		};
	protected:
		int dl; // liczba bit�w
		slowo* tab; // tablica bit�w
	public:
		explicit tab_bit(int rozm); // wyzerowana tablica bitow [0...rozm]
		explicit tab_bit(slowo tb); // tablica bit�w [0...rozmiarSlowa]

		tab_bit();//default
		tab_bit(const tab_bit& tb); // konstruktor kopiuj�cy
		tab_bit(tab_bit&& tb); // konstruktor przenosz�cy
		tab_bit& operator = (const tab_bit& tb); // przypisanie kopiuj�ce
		tab_bit& operator = (tab_bit&& tb); // przypisanie przenosz�ce
		~tab_bit(); // destruktor

	public:
		bool czytaj(int i) const; // metoda pomocnicza do odczytu bitu
		bool pisz(int i, bool b); // metoda pomocnicza do zapisu bitu
	public:
		bool operator[] (int i) const; // indeksowanie dla sta�ych tablic bitowych
		ref operator[] (int i); // indeksowanie dla zwyk�ych tablic bitowych
		inline int rozmiar() const { return this->dl; }; // rozmiar tablicy w bitach
	public:
		tab_bit& operator|=(const tab_bit& tb);
		tab_bit& operator&=(const tab_bit& tb);
		tab_bit& operator^=(const tab_bit& tb);
	};
	tab_bit operator|(const tab_bit& tb1, const tab_bit& tb2);
	tab_bit operator&(const tab_bit& tb1, const tab_bit& tb2);
	tab_bit operator^(const tab_bit& tb1, const tab_bit& tb2);
	tab_bit operator!(const tab_bit& tb);
}