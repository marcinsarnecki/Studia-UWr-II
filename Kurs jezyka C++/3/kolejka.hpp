#pragma once
#include <string>

class kolejka {
	int size, max_size, begin;
	std::string* kol;
public:
	void wloz(std::string);
	std::string wyciagnij();
	std::string naprzodzie();
	int rozmiar();
	int pojemnosc();
	void wypisz();
	kolejka& operator=(const kolejka&)noexcept;//kopiujacy
	kolejka& operator=(kolejka&&)noexcept;//przenoszacy
	kolejka();
	kolejka(int);
	kolejka(std::initializer_list<std::string>)noexcept;
	kolejka(const kolejka&)noexcept;//kopiujacy
	kolejka(kolejka&&)noexcept;//przenoszacy
	~kolejka();
};