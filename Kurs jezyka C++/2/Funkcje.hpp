#pragma once
#include "Punkt.hpp"
#include "Odcinek.hpp"
#include "Trojkat.hpp"
#include <math.h>

double odleglosc(Punkt, Punkt);
double iloczyn(Punkt, Punkt, Punkt);
bool czyProstopadle(Odcinek, Odcinek);
bool czyRownolegle(Odcinek, Odcinek);
bool czyTrojkatySieZawieraja(Trojkat, Trojkat);
bool czyTrojkatySaRozlaczne(Trojkat, Trojkat);
bool czyPrzecinajaSie(Odcinek, Odcinek);
Punkt rotacja(Punkt, Punkt, double);
Punkt punktPrzeciecia(Odcinek, Odcinek);