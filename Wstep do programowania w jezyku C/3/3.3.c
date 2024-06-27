#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int ile(int n) {
	int k = 0;
	while(n > 1) {
		for(int i = 2; i <= n; i++) if(n % i == 0) {
			 n /= i;
			 k++;
			 break;
		}
	}
	return k;	
}

int k1[20000], k3[20000], czyk7[20001], k1dx, k3dx, ans;

int main() {
	for(int i = 2; i <= 20000; i++) {
		int k = ile(i);
		if(k == 1) k1[k1dx++] = i;
		if(k == 3) k3[k3dx++] = i;
		if(k == 7) czyk7[i] = 1;
	}
	int n;
	scanf("%d", &n);
	for(int i = 0; i < k1dx; i++)
		for(int j = 0; j < k3dx; j++) {
			int sum = k1[i] + k3[j];
			if(sum > n) continue;
			if(czyk7[n - sum]) ans++;
		}
	printf("%d", ans);
	return 0;
}
