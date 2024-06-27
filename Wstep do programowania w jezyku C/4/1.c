#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int fibRec(int x) {
	if(x == 1 || x == 2)
		return 1;
	return fibRec(x - 1) + fibRec(x - 2);
}

int fibIte(int x) {
	int a = 1, b = 1, c = a + b;
	if(x == 1 || x == 2) return 1;
	for(int i = 3; i <= x; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

int fibMem[63];
int fibRecMem(int x) {
	if(fibMem[x] != 0) return fibMem[x];
	if(x == 1 || x == 2) {
		fibMem[1] = fibMem[2] = 1;
		return 1;
	}
	int ans = fibRecMem(x - 1) + fibRecMem(x - 2);
	fibMem[x] = ans;
	return ans;
}

int main() {
	int n;
	clock_t start, end;
	double total;
	scanf("%d", &n);
	
	start = clock();
	int wynik = fibRec(n);
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf("   fibRec(%d)=	%d, czas=%lf\n", n, wynik, total);
	
	start = clock();
	wynik = fibIte(n);
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf("   fibIte(%d)=	%d, czas=%lf\n", n, wynik, total);
	
	start = clock();
	wynik = fibIte(n);
	end = clock();
	total = (double) (end - start) / CLOCKS_PER_SEC;
	printf("fibRecMem(%d)=	%d, czas=%lf\n", n, wynik, total);
	
	
	
	return 0;
}
