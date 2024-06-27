#include <stdio.h>//Marcin Sarnecki lista 3 zadanie 2
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
	int system1, system2, size1 = 0, n = 0, idx = 0;
	char input[40], output[40];
	printf("Podaj system pierwszej liczby (2-16): ");
	scanf("%d", &system1);
	if(!(system1 >= 2 && system1 <= 16)) {
		printf("Zły system!\n");
		return 0;
	}
	printf("Podaj liczbe: ");
	getchar();
	scanf("%s", input);
	size1 = strlen(input);
	printf("Podaj system drugiej liczby: (2-16): ");
	scanf("%d", &system2);
	if(!(system2 >= 2 && system2 <= 16)) {
		printf("Zły system!\n");
		return 0;
	}
	int p = 1;
	for(int i = size1 - 1; i >= 0; i--) {
		int cyfra;
		if(input[i] >= '0' && input[i] <= '9') cyfra = input[i] - '0';
		else cyfra = input[i] - 'A' + 10;
		n += cyfra * p;
		p *= system1;
	}
	while(n) {
		int cyfra = n % system2;
		if(cyfra < 10) output[idx++] = cyfra + '0';
		else output[idx++] = cyfra + 'A' - 10;
		n /= system2;
	}
	for(int i = idx - 1; i >= 0; i--) printf("%c", output[i]);
	return 0;
}
