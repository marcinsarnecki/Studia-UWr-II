#include "kolejka.hpp"
#include <iostream>

void kolejka::wloz(std::string s) {
	if (size == max_size)
		return;
	kol[(begin + size) % max_size] = s;
	size++;
}

std::string kolejka::naprzodzie() {
	if (size == 0)
		return "";
	return kol[begin];
}

std::string kolejka::wyciagnij() {
	if (size == 0)
		return "";
	int temp = begin;
	begin = (begin + 1) % max_size;
	size--;
	return kol[temp];
}

int kolejka::rozmiar() {
	return size;
}

kolejka::kolejka() {
	begin = 0;
	size = 0;
	max_size = 1;//domyslnie
	kol = new std::string[max_size];
}

kolejka::kolejka(int pojemnosc) {
	begin = 0;
	size = 0;
	max_size = pojemnosc;
	kol = new std::string[max_size];
}

kolejka::kolejka(std::initializer_list<std::string> l)noexcept {
	max_size = l.size();
	size = max_size;
	begin = 0;
	kol = new std::string[max_size];
	auto it = l.begin();
	for (int i = 0; i < max_size; i++, it++) 
		kol[i] = *it;
}

kolejka::kolejka(const kolejka& q)noexcept {//kopiujacy
	begin = q.begin;
	size = q.size;
	max_size = q.max_size;
	kol = new std::string[max_size];
	std::copy(q.kol, q.kol + q.max_size, kol);
}

kolejka::kolejka(kolejka&& q) noexcept{//przenoszacy
	kol = q.kol;
	size = q.size;
	begin = q.begin;
	max_size = q.max_size;
	q.size = 0;
	q.begin = 0;
	q.max_size = 0;
	q.kol = nullptr;
}

kolejka::~kolejka() {
	delete[] kol;
}

int kolejka::pojemnosc() {
	return max_size;
}

kolejka& kolejka::operator=(kolejka&& q) noexcept {//przenoszacy
	if (&q == this)
		return *this;
	this->~kolejka();
	kol = q.kol;
	size = q.size;
	begin = q.begin;
	max_size = q.max_size;
	q.kol = nullptr;
	q.size = 0;
	q.begin = 0;
	return *this;
}

kolejka& kolejka::operator=(const kolejka& q) noexcept {//kopiujacy
	if (&q == this)
		return *this;
	this->~kolejka();
	size = q.size;
	begin = q.begin;
	max_size = q.max_size;
	kol = new std::string[max_size];
	std::copy(q.kol, q.kol + q.max_size, kol);
	return *this;
}

void kolejka::wypisz() {
	for (int i = begin, j = 0; j < size; i = (i + 1) % max_size, j++) {
		std::cout << kol[i] << "\n";
	}
}