#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)

int bomba[11][11];// 0 - puste, 1 - bomba
int plansza[11][11];// -1 nieznane X // n - ile() // 0 - znane . 
int pozostale = 9*9 - 5;

int losuj(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int ile(int y, int x) {
	int sum = 0;
	rep(i,y-1,y+1)
		rep(j,x-1,x+1)
			if(bomba[i][j]) sum++;
	return sum;
}

void wyswietl() {
	printf("  123456789\n");
	rep(i,1,9) {
		printf("%d ",i);
		rep(j,1,9) 
			if(plansza[i][j] == -1)
				printf("X");
			else if(plansza[i][j] == 0)
				printf(".");
			else printf("%d", plansza[i][j]);
		printf("\n");
	}
}

void init() {
	srand(time(NULL));
	rep(i,1,9)
		rep(j,1,9)
			plansza[i][j] = -1;
	int ile = 0;
	while(ile < 5) {
		int x = losuj(1,9), y = losuj(1,9);
		if(bomba[x][y] == 0) {
			bomba[x][y] = 1;
			ile++;
		}
	}
}

int check(int y, int x) {//czy mozna isc
	if(bomba[y][x] == 1) return 0;
	if(plansza[y][x] >= 0) return 0;
	if(ile(y,x) > 0) {
		plansza[y][x] = ile(y,x);
		pozostale--;
		return 0;
	}
	return 1;
}

void f(int y, int x) {
	rep(i,y-1,y+1)
		rep(j,x-1,x+1)
			if(ile(y,x) > 0) {
			plansza[y][x] = ile(y,x);
			pozostale--;
		}
}

void dfs(int y, int x) {
	//printf("w dfs %d %d\n",y,x);
	plansza[y][x] = 0;
	pozostale--;
	if(y+1 <= 9 && check(y+1,x) == 1) dfs(y+1,x);
	if(y-1 >= 1 && check(y-1,x) == 1) dfs(y-1,x);
	if(x+1 <= 9 && check(y,x+1) == 1) dfs(y,x+1);
	if(x-1 >= 1 && check(y,x-1) == 1) dfs(y,x-1);
	f(y,x); 
}

int main() {
	init();
	while(pozostale > 0) {
		wyswietl();
		printf("Pozostalo %d niezaminownych pol. Podaj pozycje\n",pozostale);
		int x, y;
		scanf("%d%d",&y,&x);
		if(bomba[y][x]) {
			printf("Przegrana! :(\n");
			return 0;
		}
		else {
			if(plansza[y][x] >= 0)
				continue;
			else if(ile(y,x) > 0) {
				plansza[y][x] = ile(y,x);
				pozostale--;
			}
			else
				dfs(y,x);
		}
	}
	printf("Wygrana! :)\n");
	return 0;
}
