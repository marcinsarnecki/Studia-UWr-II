#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define floatcmp 0.000001f

bool compare(float a, float b) {
	if(abs(b-a) < floatcmp) return true;
	return false;
}

void swap(float *a, float *b) {
	float c = *a;
	*a = *b;
	*b = c;
}

int main() {
	float a, b, c;
	scanf("%f%f%f", &a, &b, &c);
	if(compare(a,0)) {
		if(compare(b,0))
			if(compare(c,0))
				printf("Wszystkie liczby spełniaja rownanie\n");
			else
				printf("Brak rozwiazan\n");
		else
			printf("%g", -c/b);
	}
	else {
		float delta = (b*b) - (4 * a * c);
		if(delta > 0) {
			delta = sqrt(delta);
			float x1 = (-b-delta) / (2*a), x2 = (-b+delta) / (2*a);
			if(x1 > x2) swap(&x1, &x2);
			printf("%g %g\n", x1, x2);
		}
		else if(compare(delta,0))
			printf("%g\n", -b/(2*a));
		else
			printf("delta < 0, brak rozwiazan\n");
	}
	return 0;
}
