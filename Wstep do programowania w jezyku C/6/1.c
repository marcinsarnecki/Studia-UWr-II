#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int *MaxElem(int *tab, int n) {
	if(n == 0) return tab;
	int *ptr = tab;
	for(int i = 1; i < n; i++) if(tab[i] > *ptr) ptr = tab + i;
	return ptr;
}

double srednia(int *tab, int n) {
	if(n == 0) return 0;
	double sum = 0;
	for(int i = 0; i < n; i++) sum += tab[i];
	sum /= n;
	return sum;
}

void wypisz(int *tab, int n) {
	printf("Jest %d elementów:\n", n);
	for(int i = 0; i < n; i++) printf("%d ", tab[i]);
	printf("\n");
}

int ileParzystych(int *tab, int n) {
	int ile = 0;
	for(int i = 0; i < n; i++) if(tab[i] % 2 == 0) ile++;
	return ile;
	
}

void Odwroc(int *tab, int n) {
	for(int i = 0, j = n-1; i < j; i++, j--) swap(tab+i, tab+j);
}

void Sortuj(int *tab, int n) {
	for(int i = n-1; i >= 0; i--)
		for(int j = 0; j < i-1; j++)
			if(tab[j] < tab[j+1]) 
				swap(&tab[j],&tab[j+1]);
}

int main() {
	int n;
	scanf("%d", &n);
	int *tab = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
		scanf("%d", tab + i);
	int *a = MaxElem(tab, n);
	printf("Max:			%d\n", *a);
	double b = srednia(tab,n);
	printf("Srednia:		%lf\n",b);
	int c = ileParzystych(tab,n);
	printf("Ile parzystych: 	%d\n",c);
	printf("Odwracam elementy!\n");
	Odwroc(tab,n);
	wypisz(tab,n);
	printf("Sortuje!\n");
	Sortuj(tab,n);
	wypisz(tab,n);
	return 0;
}
