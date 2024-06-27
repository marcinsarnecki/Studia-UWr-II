#pragma once
#include<iostream>
#include<math.h>
#include<algorithm>

class Wielomian
{
private:
    int n;      // stopien
    double* a;  // wspolczynniki

public:
    int stopien();
    Wielomian();
    Wielomian(int, double);   // default    
    Wielomian(std::initializer_list<double>); 
    Wielomian(const Wielomian&);    //kopiujacy
    Wielomian(Wielomian&&);         //przenoszacy
    Wielomian& operator=(const Wielomian&);   //kopiujacy
    Wielomian& operator=(Wielomian&&);        //przenoszacy

    ~Wielomian();

    friend std::istream& operator >> (std::istream&, Wielomian&);
    friend std::ostream& operator << (std::ostream&, const Wielomian&);

    friend Wielomian operator+(const Wielomian&, const Wielomian&);
    friend Wielomian operator-(const Wielomian&, const Wielomian&);
    friend Wielomian operator*(const Wielomian&, const Wielomian&);
    friend Wielomian operator*(const Wielomian&, double c);

    Wielomian& operator += (const Wielomian& Wielomian);
    Wielomian& operator -= (const Wielomian& Wielomian);
    Wielomian& operator *= (const Wielomian& Wielomian);
    Wielomian& operator *= (double c);
    
    double operator () (double) const;
    double operator [] (int) const;       
};