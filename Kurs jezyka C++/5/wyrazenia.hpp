#pragma once
#include <iostream>
#include <string>
#include <vector>



class wyrazenie {
public:
	virtual double oblicz() = 0;
	virtual std::string zapis() = 0;
	virtual int priorytet() {
		return 9;
	}
	virtual bool czyLewostronne() {
		return true;
	}
	virtual ~wyrazenie() {};
    wyrazenie() {};
    wyrazenie(const wyrazenie&) = delete;
    wyrazenie(wyrazenie&&) = delete;
    wyrazenie& operator=(const wyrazenie&) = delete;
    wyrazenie& operator=(wyrazenie&&) = delete;
};

class liczba : public wyrazenie {
public:
	double wartosc;
	liczba(double);
	std::string zapis();
	double oblicz();
};


class zmienna : public wyrazenie {
	static std::vector<std::pair<std::string, double>> v;
public:
	static void dodajZmienna(std::string z, double wartosc);
	static void zmodyfikujZmienna(std::string z, double wartosc);
	static void usunZmienna(std::string z);

	std::string nazwa;
	zmienna(std::string);
	std::string zapis();
	double oblicz();
};

class stala : public wyrazenie {
protected:
	double wartosc = 0;
};

class pi : public stala
{
public:
	std::string zapis();
	double oblicz();
	pi();
};

class e : public stala
{
public:
	std::string zapis();
	double oblicz();
	e();
};

class fi : public stala
{
public:
	std::string zapis();
	double oblicz();
	fi();
};

class operator1arg : public wyrazenie {
protected:
    wyrazenie* arg1;
public:
	operator1arg(wyrazenie*);
};

class przeciw : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	przeciw(wyrazenie* arg1);
};

class odwrot : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	odwrot(wyrazenie* arg1);
};

class bezwzgl : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	bezwzgl(wyrazenie* arg1);
};

class Exp : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	Exp(wyrazenie* arg1);
};

class ln : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	ln(wyrazenie* arg1);
};

class sinus : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	sinus(wyrazenie*);
};

class cosinus : public operator1arg
{
public:
	std::string zapis();
	double oblicz();
	cosinus(wyrazenie*);
};

class operator2arg : public operator1arg
{
protected:
    wyrazenie* arg2;
public:
	int priorytet() override
	{
		return 1;
	}
	operator2arg(wyrazenie*, wyrazenie*);
	virtual bool czyLewostronne() = 0;
};

class dodaj : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    bool czyLewostronne() override
    {
        return true;
    }

    dodaj(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class odejmij : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    bool czyLewostronne() override
    {
        return true;
    }

    odejmij(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class mnoz : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    int priorytet() override
    {
        return 2;
    }

    bool czyLewostronne() override
    {
        return true;
    }

    mnoz(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class dziel : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    int priorytet() override
    {
        return 2;
    }

    bool czyLewostronne() override
    {
        return true;
    }

    dziel(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class potega : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    int priorytet() override
    {
        return 3;
    }

    bool czyLewostronne() override
    {
        return true;
    }

    potega(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class modulo : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    int priorytet() override
    {
        return 3;
    }

    bool czyLewostronne() override
    {
        return true;
    }

    modulo(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {}
};

class logarytm : public operator2arg
{
public:
    std::string zapis();
    double oblicz();

    int priorytet() override
    {
        return 3;
    }

    bool czyLewostronne() override
    {
        return true;
    }

    logarytm(wyrazenie* arg1, wyrazenie* arg2) : operator2arg(arg1, arg2) {};
};

