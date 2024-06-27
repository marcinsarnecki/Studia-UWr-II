#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
	unsigned int a;
	scanf("%d", &a);
	int ile1 = 0, longest1 = 0, longest0 = 0, curr1 = 0, curr0 = 0;
	for(int i = 0; i < 32; i++) {
		if(a & (1<<i)) {
			ile1++;
			curr1++;
			curr0 = 0;
			if(longest1 < curr1) longest1 = curr1;
		}
		else {
			curr0++;
			curr1 = 0;
			if(longest0 < curr0) longest0 = curr0;
		}
	}
	printf("liczba jedynek: %d\nnajdluzszy ciag 1: %d\nnajdluzszy ciag 0: %d\n", ile1, longest1, longest0);
	
	return 0;
}
