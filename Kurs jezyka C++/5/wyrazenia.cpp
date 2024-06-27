#include "wyrazenia.hpp"
#include <math.h>

std::vector<std::pair<std::string, double>> zmienna::v;

liczba::liczba(double wartosc)
{
    this->wartosc = wartosc;
}

std::string liczba::zapis()
{
    std::string str = std::to_string(wartosc);
    return str;
}

double liczba::oblicz()
{
    return wartosc;
}

zmienna::zmienna(std::string var)
{
    this->nazwa = var;
}

std::string zmienna::zapis()
{
    return nazwa;
}

double zmienna::oblicz()
{
    try
    {
        int ile = zmienna::v.size();
        for (int i = 0; i < ile; i++)
            if (zmienna::v[i].first == nazwa)
                return zmienna::v[i].second;

        std::string err = "Nie znaleziono zmiennej";
        throw err;
    }
    catch (std::string err_msg)
    {
        std::cerr << "Blad: " << err_msg << " w trakcie funkcji oblicz(), podstawiam 0 zamiast " << nazwa << ".\n";
        return 0;
    }
}

void zmienna::dodajZmienna(std::string z, double wartosc)
{
    int ile = zmienna::v.size();
    for (int i = 0; i < ile; i++)
    {
        if (zmienna::v[i].first == z)
        {
            std::cout << "Zmienna " << z << " zostala juz wczesniej dodana, jej wartosc wynosi " << zmienna::v[i].second << std::endl;
            return;
        }
    }

    zmienna::v.push_back(make_pair(z, wartosc));
}

void zmienna::zmodyfikujZmienna(std::string z, double wartosc) 
{
    int ile = zmienna::v.size();
    for (int i = 0; i < ile; i++)
    {
        if (zmienna::v[i].first == z)
        {
            zmienna::v[i].second = wartosc;
            return;
        }
    }
}

void zmienna::usunZmienna(std::string z)
{
    try
    {
        int ile = zmienna::v.size();
        for (int i = 0; i < ile; i++)
        {
            if (zmienna::v[i].first == z)
            {
                zmienna::v.erase(zmienna::v.begin() + i);
                return;
            }
        }
        std::string err = "Nie znaleziono zmiennej " + z + " podczas usuwania";
        throw err;
    }
    catch (std::string err)
    {
        std::cerr << "Blad: " << err << " w trakcie funkcji usunZmienna().\n";
    }
}



pi::pi()
{
    wartosc = 3.141592653589;
}

std::string pi::zapis()
{
    return "pi";
}

double pi::oblicz()
{
    return wartosc;
}

e::e()
{
    wartosc = 2.7182818284;
}

std::string e::zapis()
{
    return "e";
}

double e::oblicz()
{
    return wartosc;
}

fi::fi()
{
    wartosc = 1.618;
}

std::string fi::zapis()
{
    return "fi";
}

double fi::oblicz()
{
    return wartosc;
}

operator1arg::operator1arg(wyrazenie* arg1)
{
    this->arg1 = arg1;
}

przeciw::przeciw(wyrazenie* arg1) : operator1arg(arg1) {}

std::string przeciw::zapis()
{
    return "-(" + arg1->zapis() + ")";
}

double przeciw::oblicz()
{
    return (-1) * arg1->oblicz();
}

odwrot::odwrot(wyrazenie* arg1) : operator1arg(arg1) {}

std::string odwrot::zapis()
{
    return "1 / " + arg1->zapis();
}

double odwrot::oblicz()
{
    return 1.0 / arg1->oblicz();
}

bezwzgl::bezwzgl(wyrazenie* arg1) : operator1arg(arg1) {}

std::string bezwzgl::zapis()
{
    return "|" + arg1->zapis() + "|";
}

double bezwzgl::oblicz()
{
    if (arg1->oblicz() < 0)
        return (-1) * arg1->oblicz();
    else
        return arg1->oblicz();
}

Exp::Exp(wyrazenie* arg1) : operator1arg(arg1) {}

std::string Exp::zapis()
{
    return "exp(" + arg1->zapis() + ")";
}

double Exp::oblicz()
{
    return exp(arg1->oblicz());
}

ln::ln(wyrazenie* arg1) : operator1arg(arg1) {}

std::string ln::zapis()
{
    return "ln(" + arg1->zapis() + ")";
}

double ln::oblicz()
{
    return log(arg1->oblicz());
}

sinus::sinus(wyrazenie* arg1) : operator1arg(arg1) {}

std::string sinus::zapis()
{
    return "sin(" + arg1->zapis() + ")";
}

double sinus::oblicz()
{
    return sin(arg1->oblicz());
}

cosinus::cosinus(wyrazenie* arg1) : operator1arg(arg1) {}

std::string cosinus::zapis()
{
    return "cos(" + arg1->zapis() + ")";
}

double cosinus::oblicz()
{
    return cos(arg1->oblicz());
}

operator2arg::operator2arg(wyrazenie* arg1, wyrazenie* arg2) : operator1arg(arg1)
{
    this->arg2 = arg2;
}

std::string dodaj::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())//jesli lewe dziecko ma mniejszy priorytet to trzeba uzyc nawiasow
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne())
        left = arg1->zapis(); 
    else                                //jesli ten sam priorytet i nie jest lewostronne 
        left = "(" + arg1->zapis() + ")";
    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())//jesli prawe dziecko ma mniejszy priorytet to trzeba uzyc nawiasow
        right = "(" + arg2->zapis() + ")";
    else if (arg2->czyLewostronne())
        right = arg2->zapis(); 
    else
        right = "(" + arg2->zapis() + ")";

    return left + " + " + right;
}

double dodaj::oblicz()
{
    return arg1->oblicz() + arg2->oblicz();
}

std::string odejmij::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne())
        left = arg1->zapis(); 
    else
        left = "(" + arg1->zapis() + ")";
    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())
        right = "(" + arg2->zapis() + ")";
    else if (!arg2->czyLewostronne())
        right = arg2->zapis(); 
    else
        right = "(" + arg2->zapis() + ")";

    return left + " - " + right;
}

double odejmij::oblicz()
{
    return arg1->oblicz() - arg2->oblicz();
}

std::string mnoz::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne() == true)
        left = arg1->zapis(); 
    else
        left = "(" + arg1->zapis() + ")";

    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())
        right = "(" + arg2->zapis() + ")";
    else if (arg2->czyLewostronne() == true)
        right = arg2->zapis(); 
    else
        right = "(" + arg2->zapis() + ")";

    return left + " * " + right;
}

double mnoz::oblicz()
{
    return arg1->oblicz() * arg2->oblicz();
}

std::string dziel::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne() == true)
        left = arg1->zapis(); 
    else
        left = "(" + arg1->zapis() + ")";

    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())
        right = "(" + arg2->zapis() + ")";
    else if (arg2->czyLewostronne() == true)
        right = arg2->zapis(); 
    else
        right = "(" + arg2->zapis() + ")";

    return left + " / " + right;
}

double dziel::oblicz()
{
    return arg1->oblicz() / arg2->oblicz();
}

std::string potega::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne() == true)
        left = arg1->zapis(); 
    else
        left = "(" + arg1->zapis() + ")";

    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())
        right = "(" + arg2->zapis() + ")";
    else if (arg2->czyLewostronne() == true)
        right = arg2->zapis(); 
    else
        right = "(" + arg2->zapis() + ")";

    return left + " ^ " + right;
}

double potega::oblicz()
{
    return pow(arg1->oblicz(), arg2->oblicz());
}

std::string modulo::zapis()
{
    std::string left, right;

    if (arg1->priorytet() > priorytet())
        left = arg1->zapis();
    else if (arg1->priorytet() < priorytet())
        left = "(" + arg1->zapis() + ")";
    else if (arg1->czyLewostronne() == true)
        left = arg1->zapis(); 
    else
        left = "(" + arg1->zapis() + ")";

    if (arg2->priorytet() > priorytet())
        right = arg2->zapis();
    else if (arg2->priorytet() < priorytet())
        right = "(" + arg2->zapis() + ")";
    else if (arg2->czyLewostronne() == true)
        right = arg2->zapis();
    else
        right = "(" + arg2->zapis() + ")";

    return left + " % " + right;
}

double modulo::oblicz()
{
    return fmod(arg1->oblicz(), arg2->oblicz());
}

std::string logarytm::zapis()
{
    return "logarytm(" + arg1->zapis() + ", " + arg2->zapis() + ")";
}

double logarytm::oblicz()
{
    double e1, e2;

    e1 = log(arg1->oblicz());
    e2 = log(arg2->oblicz());

    return e2 / e1;
}