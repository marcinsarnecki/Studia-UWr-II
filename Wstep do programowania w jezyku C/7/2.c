#include <stdio.h> 
#include <stdlib.h> 
  
typedef struct ulamek{
	int l, m;
}ulamek; 

ulamek utworz(int licznik, int mianownik) {//corner case m = 0!!
	ulamek a;
	a.l = licznik;
	a.m = mianownik;
	return a;
}

int gcd(int a, int b) {
    if (b != 0)
        return gcd(b, a % b);
    else
        return a;
}

ulamek suma(ulamek a, ulamek b) {
	ulamek ans;
	ans.m = a.m * b.m / gcd(a.m, b.m);
	ans.l = a.l * (ans.m / a.m) + b.l * (ans.m / b.m);
	return ans;
}

ulamek roznica(ulamek a,ulamek b) {
	ulamek ans;
	ans.m = a.m * b.m / gcd(a.m, b.m);
	ans.l = a.l * (ans.m / a.m) - b.l * (ans.m / b.m);
	return ans;
}

ulamek iloczyn(ulamek a,ulamek b) {
	ulamek ans;
	ans.l = a.l * b.l;
	ans.m = a.m * b.m;
	return ans;
}

ulamek iloraz(ulamek a,ulamek b) {
	ulamek ans;
	ans.l = a.l * b.m;
	ans.m = a.m * b.l;
	return ans;
}

ulamek uprosc(ulamek a) {
	ulamek ans;
	int nwd = gcd(a.l, a.m);
	ans.l = a.l / nwd;
	ans.m = a.m / nwd;
	return ans;
}
void wypisz(ulamek a) {
	a = uprosc(a);
	int full = a.l / a.m;
	if(full > 0) {
		printf("%d ", full);
		a.l %= a.m;
		if(a.l != 0) printf("%d/%d", a.l, a.m);
	}
	else {
		printf("%d/%d", a.l, a.m);
	}
	printf("\n");
}
int main() 
{
	ulamek a;
	scanf("%d%d", &a.l, &a.m);
	ulamek b;
	scanf("%d%d", &b.l, &b.m);
	if(a.m == 0 || b.m == 0)
		return 0;
	ulamek ans;
	ans = suma(a,b);
	printf("suma: "); wypisz(ans);
    ans = roznica(a,b);
	printf("roznica: "); wypisz(ans);
	ans = iloczyn(a,b);
	printf("iloczyn: "); wypisz(ans);
	ans = iloraz(a,b);
	printf("iloraz: "); wypisz(ans);
  
    return 0; 
}
