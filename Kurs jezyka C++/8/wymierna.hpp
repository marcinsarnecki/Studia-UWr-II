#pragma once

#include <iostream>
#include <climits>
#include <vector>
#include <stdexcept>

namespace obliczenia
{
	class wyjatekwymierny : std::logic_error {
	public:
		wyjatekwymierny(const std::string& m) : logic_error(m) {};
	};
	class dzielenie_przez_0 : wyjatekwymierny {
	public:
		dzielenie_przez_0() : wyjatekwymierny("Dzielenie przez 0!") {};
	};
	class przekroczenie_zakresu : wyjatekwymierny {
	public:
		przekroczenie_zakresu() : wyjatekwymierny("Zakres przekroczony") {};
	};

	int nwd(int a, int b);

	class wymierna
	{
	public:
		int licznik, mianownik;
		void uprosc();

		int getLicznik();
		int getMianownik();

		wymierna(int num, int den);    // create num/den
		wymierna(int num);			    // create num/1

		friend wymierna operator - (wymierna a);				            // przeciwna (-x)
		friend wymierna operator ! (wymierna a);				            // odwrotnosc (1/x)
		friend wymierna operator + (const wymierna& a, const wymierna& b);  // a + b
		friend wymierna operator - (const wymierna& a, const wymierna& b);	// a - b
		friend wymierna operator * (const wymierna& a, const wymierna& b);	// a * b
		friend wymierna operator / (const wymierna& a, const wymierna& b);	// a / b

		wymierna& operator += (const wymierna& x); 
		wymierna& operator -= (const wymierna& x); 
		wymierna& operator *= (const wymierna& x); 
		wymierna& operator /= (const wymierna& x); 

		operator double() const noexcept;			// rzutowanie na double
		operator int() const noexcept;				// rzutowanie na int

		friend std::ostream& operator << (std::ostream& output, const wymierna& x);
	};
}