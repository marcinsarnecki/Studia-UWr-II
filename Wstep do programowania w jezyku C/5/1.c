#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define floatcmp 0.000001f

void swap(float *a, float *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int main() {
	float a, b, c;
	scanf("%f%f%f", &a, &b, &c);
	if (a > b) swap(&a, &b);
	if (b > c) swap(&b, &c);
	if (a > b) swap(&a, &b);
	const bool czyTrojkat = (a + b > c);
	if (czyTrojkat) 													printf("a) Tak\n");
	else 																printf("a) Nie\n");
	if (abs((a*a) + (b*b) - (c*c)) < floatcmp) 							printf("b) Tak\n");
	else  																printf("b) Nie\n");
	if (czyTrojkat && ((abs(a-b) < floatcmp) && (abs(c-b) < floatcmp))) printf("c) Tak\n");
	else  																printf("c) Nie\n");
	if (czyTrojkat && ((abs(a-b) < floatcmp) || (abs(c-b) < floatcmp))) printf("d) Tak\n");
	else  																printf("d) Nie\n");
	return 0;
}
