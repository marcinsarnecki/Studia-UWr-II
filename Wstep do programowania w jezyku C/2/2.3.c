#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 128
char mode[N], input[N], output[N];
int size1, size2, kol[N][7], idx;

void wczytaj(char* p, int *size) {//wczytuje do znaku konca lini
	int idx = 0;
	while(1) {
		int c = getchar();
		if(c == '\n') break;
		p[idx++] = c;
		(*size)++;
	}
}

int main() {
	wczytaj(mode, &size1);
	if(strcmp(mode, "encode") == 0) {
		wczytaj(input, &size2);
		if(size2 > 64)
			return 0;
		if(size2 % 8 != 0) size2 += 8 - (size2 % 8);
		for(int i = 0; i < size2; i++) {
			for(int j = 0; j < 7; j++)
				if(input[i] & (1<<j)) kol[i][j] = 1;
				else kol[i][j] = 0;
		}
		for(int j = 0; j < 7; j++)
			for(int i = 0; i < size2; i += 4) {
				int c = kol[i][j] * 8 + kol[i+1][j] * 4 + kol[i+2][j] * 2 + kol[i+3][j];
				if(c < 10) output[idx++] = c + '0';
				else output[idx++] = c - 10 + 'A';
			}
		printf("%s\n", output);
	}
	if(strcmp(mode, "decode") == 0) {
		wczytaj(input, &size2);
		int n = size2 / 7;
		for(int j = 0; j < 7; j++) {
			idx = 0;
			for(int i = 0; i < n; i++) {
				int c = input[j*n + i];
				if(c <= '9') c -= '0';
				else c = c - 'A' + 10;
				if(c & (1<<3)) kol[idx++][j] = 1;
					else kol[idx++][j] = 0;
				if(c & (1<<2)) kol[idx++][j] = 1;
					else kol[idx++][j] = 0;
				if(c & (1<<1)) kol[idx++][j] = 1;
					else kol[idx++][j] = 0;
				if(c & (1<<0)) kol[idx++][j] = 1;
					else kol[idx++][j] = 0;
			}
		}
		size2 = n * 4;
		for(int i = 0; i < size2; i++) {
			output[i] = 0;
			for(int j = 0; j < 7; j++)
				output[i] += kol[i][j] * (1<<j);
		}
		printf("%s\n", output);
	}
	return 0;
}
