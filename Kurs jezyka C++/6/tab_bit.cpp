#include "tab_bit.hpp"
#include <string>

namespace obliczenia {
	tab_bit::tab_bit(int rozm) {
		int ile = rozm / tab_bit::rozmiarSlowa;
		if (rozm % tab_bit::rozmiarSlowa != 0)
			ile++;
		this->dl = rozm;
		this->tab = new slowo[ile];
		for (int i = 0; i < ile; i++)
			tab[i] = uint64_t(0);
	}

	tab_bit::tab_bit(slowo tb) {
		this->dl = rozmiarSlowa;
		this->tab = new slowo[1];
		tab[0] = tb;
	}

	tab_bit::tab_bit() {
		dl = 0;
		tab = nullptr;
	}

	tab_bit::tab_bit(const tab_bit& tb) { //konstruktor kopiujacy
		int rozmiar = tb.rozmiar();
		this->tab = new slowo[rozmiar];
		this->dl = tb.dl;
		for (int i = 0; i < rozmiar; i++)
			this->tab[i] = tb.tab[i];
	}

	tab_bit::tab_bit(tab_bit&& tb) //konstruktor przenoszacy
	{
		this->dl = tb.dl;
		this->tab = tb.tab;
		tb.dl = 0;
		tb.tab = nullptr;
	}

	tab_bit& tab_bit::operator=(const tab_bit& tb) { //przypisanie kopiujace
		if (&tb == this)
			return *this;
		this->~tab_bit();
		int rozmiar = tb.rozmiar();
		this->dl = tb.dl;
		for (int i = 0; i < rozmiar; i++)
			this->tab[i] = tb.tab[i];
		return *this;
	}

	tab_bit& tab_bit::operator=(tab_bit&& tb) { //przypisane przenoszace
		if (&tb == this)
			return *this;
		this->~tab_bit();
		this->dl = tb.dl;
		this->tab = tb.tab;
		tb.dl = 0;
		tb.tab = nullptr;
		return *this;
	}

	tab_bit::~tab_bit() { //destruktor
		delete[] this->tab;
	}

	tab_bit::ref::ref(int i, slowo* s) {
		idx = i;
		ptr = s;
	}

	tab_bit::ref::operator bool()const {
		return (bool)((*ptr) & (uint64_t(1) << this->idx));
	}

	tab_bit::ref& tab_bit::ref::operator=(bool b) {
		*this->ptr = (*this->ptr & (~(uint64_t(1) << (this->idx))));//wyzerowanie bitu
		*this->ptr |= ((uint64_t)b << (this->idx));
		return *this;
	}

	tab_bit::ref& tab_bit::ref::operator=(const ref& bit) { //POJEDYNCZY BIT
		*this = (bool)bit;
		return *this;
	}

	bool tab_bit::czytaj(int i) const {
		if (i >= this->dl || i < 0)
			throw std::invalid_argument("Indeks spoza zakresu");
		int wiersz = i / tab_bit::rozmiarSlowa;
		int idx = i - wiersz * tab_bit::rozmiarSlowa;
		return (bool)ref(idx, &(this->tab[wiersz]));
	}

	bool tab_bit::pisz(int i, bool b) { //dlaczego bool?
		if (i >= this->dl || i < 0)
			throw std::invalid_argument("Indeks spoza zakresu");
		int wiersz = i / tab_bit::rozmiarSlowa;
		int idx = i - wiersz * tab_bit::rozmiarSlowa;
		ref bit(idx, &(this->tab[wiersz]));
		bit = b;
		return b;
	}

	bool tab_bit::operator[](int i) const {
		if (i >= this->dl || i < 0)
			throw std::invalid_argument("Indeks spoza zakresu");
		return this->czytaj(i);
	}

	tab_bit::ref tab_bit::operator[](int i) {
		if (i >= this->dl || i < 0)
			throw std::invalid_argument("Indeks spoza zakresu");
		int wiersz = i / tab_bit::rozmiarSlowa;
		int idx = i - wiersz * tab_bit::rozmiarSlowa;
		return ref(idx, &(this->tab[wiersz]));
	}

	std::istream& operator>>(std::istream& we, tab_bit& tb)
	{
		std::string s;
		we >> s;
		int len = s.size();
		tb.~tab_bit();
		int ile = len / tab_bit::rozmiarSlowa;
		if (len % tab_bit::rozmiarSlowa != 0)
			ile++;
		tb.tab = new tab_bit::slowo[ile];
		tb.dl = len;
		for (int i = 0; i < len; i++) {
			int x = s[i] - 48;
			if (x != 0 && x != 1)
				throw std::invalid_argument("Wpisano inny znak niz 0 i 1");
			tb[i] = (bool)x;
		}
		return we;
	}

	std::ostream& operator<<(std::ostream& wy, const tab_bit& tb) {
		for (int i = 0; i < tb.dl; i++)
			wy << tb[i];
		return wy;
	}

	tab_bit operator!(const tab_bit& tb)
	{
		tab_bit wynik(tb);
		for (int i = 0; i < tb.rozmiar(); i++)
			wynik[i] = !tb[i];
		return wynik;
	}

	tab_bit operator^(const tab_bit& tb1, const tab_bit& tb2)
	{
		tab_bit wynik(tb1.rozmiar() > tb2.rozmiar() ? tb1 : tb2);
		int mini = tb1.rozmiar() > tb2.rozmiar() ? tb2.rozmiar() : tb1.rozmiar();
		for (int i = 0; i < mini; i++)
			wynik[i] = tb1[i] ^ tb2[i];
		return wynik;
	}

	tab_bit operator&(const tab_bit& tb1, const tab_bit& tb2)
	{
		tab_bit wynik(tb1.rozmiar() > tb2.rozmiar() ? tb1 : tb2);
		int mini = tb1.rozmiar() > tb2.rozmiar() ? tb2.rozmiar() : tb1.rozmiar();
		for (int i = 0; i < mini; i++)
			wynik[i] = tb1[i] & tb2[i];
		return wynik;
	}

	tab_bit operator|(const tab_bit& tb1, const tab_bit& tb2)
	{
		tab_bit wynik(tb1.rozmiar() > tb2.rozmiar() ? tb1 : tb2);
		int mini = tb1.rozmiar() > tb2.rozmiar() ? tb2.rozmiar() : tb1.rozmiar();
		for (int i = 0; i < mini; i++)
			wynik[i] = tb1[i] | tb2[i];
		return wynik;
	}

	tab_bit& tab_bit::operator|=(const tab_bit& tb)
	{
		tab_bit wynik = (*this | tb);
		*this = std::move(wynik);
		return *this;
	}

	tab_bit& tab_bit::operator&=(const tab_bit& tb)
	{
		tab_bit wynik = (*this & tb);
		*this = std::move(wynik);
		return *this;
	}

	tab_bit& tab_bit::operator^=(const tab_bit& tb)
	{
		tab_bit wynik = (*this ^ tb);
		*this = std::move(wynik);
		return *this;
	}
}