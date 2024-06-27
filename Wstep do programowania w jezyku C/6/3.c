#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)

int plansza[410][410];
int currentX = 202, currentY = 202;
int dir = 1;// 0 1 2 3 gora prawo dol lewo
char input[201];
int minY = 405, maxY, minX = 405, maxX;

int main() {
	plansza[currentY][currentX] = 1;
	scanf("%s", input);
	for(int i = 0; i < (int)strlen(input); i++) {
		if(input[i] == 'F') {
				if(dir == 0)
					currentY--;
				if(dir == 1)
					currentX++;
				if(dir == 2)
					currentY++;
				if(dir == 3)
					currentX--;
				plansza[currentY][currentX] = 1;
			}
		if(input[i] == 'L')
			dir = (dir-1) < 0 ? 3 : dir - 1;
		if(input[i] == 'R') 
			dir = (dir+1) % 4;
	}
	for(int i = 1; i <= 405; i++)
		for(int j = 1; j <= 405; j++) 
			if(plansza[i][j]) {
				minY = fmin(minY, i);
				maxY = fmax(maxY, i);
				minX = fmin(minX, j);
				maxX = fmax(maxX, j);
			}
	for(int i = minY; i <= maxY; i++) {
		for(int j = minX; j <= maxX; j++)
			plansza[i][j] ? printf("*") : printf(" ");
		printf("\n");
	}
	return 0;
}
