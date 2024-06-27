#include "wymierna.hpp"

namespace obliczenia
{
    int nwd(int a, int b)
    {
        if (b == 0)
            return a;
        return nwd(b, a % b);
    }

    int wymierna::getLicznik() {
        return this->licznik;
    }

    int wymierna::getMianownik() {
        return this->mianownik;
    }

    void wymierna::uprosc()
    {
        int l = this->licznik;
        int m = this->mianownik;
        int d = nwd(l,m);

        l /= d;
        m /= d;

        if (m < 0) {
            m *= (-1);
            l *= (-1);
        }

        this->licznik = l;
        this->mianownik = m;
    }

    wymierna::wymierna(int l, int m) // create num/den
    {
        if (m == 0)
            throw dzielenie_przez_0();

        this->licznik = l;
        this->mianownik = m;
        uprosc();
    }

    wymierna::wymierna(int num) // create num/1
    {
        this->licznik = num;
        this->mianownik = 1;
    }

    wymierna operator - (wymierna a) // a becomes -a
    {
        a.licznik *= (-1);
        return a;
    }

    wymierna operator ! (wymierna a) // a = p/q becomes q/p
    {
        if (a.licznik == 0)
            throw dzielenie_przez_0();

        int temp = a.licznik;
        a.licznik = a.mianownik;
        a.mianownik = temp;
        a.uprosc();
        return a;
    }

    wymierna operator + (const wymierna& a, const wymierna& b) // a + b
    {
        long long tempN = (long long) a.licznik * b.mianownik + (long long)b.licznik * a.mianownik;
        long long tempD = (long long) a.mianownik * b.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        wymierna wynik(a.licznik * b.mianownik + b.licznik * a.mianownik, a.mianownik * b.mianownik);
        wynik.uprosc();

        return wynik;
    }

    wymierna operator - (const wymierna& a, const wymierna& b) // a - b
    {
        long long tempN = (long long)a.licznik * b.mianownik - (long long)b.licznik * a.mianownik;
        long long tempD = (long long)a.mianownik * b.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        wymierna wynik(a.licznik * b.mianownik - b.licznik * a.mianownik, a.mianownik * b.mianownik);
        wynik.uprosc();

        return wynik;
    }

    wymierna operator * (const wymierna& a, const wymierna& b) // a * b
    {
        long long tempN = (long long)a.licznik * b.licznik;
        long long tempD = (long long)a.mianownik * b.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        wymierna wynik(a.licznik * b.licznik, a.mianownik * b.mianownik);
        wynik.uprosc();

        return wynik;
    }

    wymierna operator / (const wymierna& a, const wymierna& b) // a / b
    {
        if (b.licznik == 0)
            throw dzielenie_przez_0();

        long long tempN = (long long)a.licznik * b.mianownik;
        long long tempD = (long long)a.mianownik * b.licznik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        wymierna wynik(a.licznik * b.mianownik, a.mianownik * b.licznik);
        wynik.uprosc();

        return wynik;
    }


    wymierna& wymierna::operator += (const wymierna& x) // this += x equals this = this + x
    {
        long long tempN = (long long)this->licznik * x.mianownik + (long long)x.licznik * this->mianownik;
        long long tempD = (long long)this->mianownik * x.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        this->licznik = this->licznik * x.mianownik + x.licznik * this->mianownik;
        this->mianownik = this->mianownik * x.mianownik;
        uprosc();

        return *this;
    }

    wymierna& wymierna::operator -= (const wymierna& x) // this -= x equals this = this - x
    {
        long long tempN = (long long)this->licznik * x.mianownik - (long long)x.licznik * this->mianownik;
        long long tempD = (long long)this->mianownik * x.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        this->licznik = this->licznik * x.mianownik - x.licznik * this->mianownik;
        this->mianownik = this->mianownik * x.mianownik;
        uprosc();

        return *this;
    }

    wymierna& wymierna::operator *= (const wymierna& x) // this *= x equals this = this * x
    {
        long long tempN = (long long)this->licznik * x.licznik;
        long long tempD = (long long)this->mianownik * x.mianownik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        this->licznik = this->licznik * x.licznik;
        this->mianownik = this->mianownik * x.mianownik;
        uprosc();

        return *this;
    }

    wymierna& wymierna::operator /= (const wymierna& x) 
    {
        if (x.licznik == 0)
            throw dzielenie_przez_0();

        long long tempN = (long long)this->licznik * x.mianownik;
        long long tempD = (long long)this->mianownik * x.licznik;
        if (tempN > INT_MAX || tempN < INT_MIN || tempD > INT_MAX || tempD < INT_MIN)
            throw przekroczenie_zakresu();

        this->licznik = this->licznik * x.mianownik;
        this->mianownik = this->mianownik * x.licznik;
        uprosc();

        return *this;
    }

    wymierna::operator double() const noexcept
    {
        return (double)this->licznik / this->mianownik;
    }

    wymierna::operator int() const noexcept
    {
        return int(round((double)this->licznik / this->mianownik));
    }

    std::ostream& operator << (std::ostream& output, const obliczenia::wymierna& x)
    {
        int l = x.licznik;
        int d = x.mianownik;
        while (d % 2 == 0)
            d /= 2;
        while (d % 5 == 0)
            d /= 5;
        if (d == 1) 
            return output << double(x);
        int d1 = x.licznik;
        int d2 = x.mianownik;
        int calkowita = d1 / d2;
        int reszta = d1 % d2;
        output << calkowita;
        d1 -= calkowita * d2;
        std::vector<std::pair<char, int>> states;
        int start = 0;
        while (reszta) {
             reszta *= 10;
             int r = reszta / d2;
             char cyfra = r + '0';//przesuniecie w ascii
             reszta = reszta - r * d2;//aktualizacja reszty
             std::pair<char,int> current = std::make_pair(cyfra, reszta);
             states.push_back(current);
             for (unsigned int i = 0; i < states.size() - 1; i++) {
                 if (current == states[i]) {
                     start = i;
                     reszta = 0;
                     states.pop_back();
                     break;
                 }
             }
         }
        output << ".";
        int i = 0;
        for (auto& state : states)
        {
            if (i == start)
                output << "(";
                output << state.first;
                i++;
        }
        output << ")";
        return output;
    }
}