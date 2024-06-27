#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define trawa 0
#define mur 1
#define jagoda 2
#define teleport 3
#define wyjscie 4

int n, e, xs, ys, plansza[50][50], ans = -1;
bool visited[50][50];

void wej() {
	scanf("%d%d%d%d", &n, &e, &xs, &ys);
	getchar();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			char z;
			scanf("%c", &z);
			if(z == '.') plansza[i][j] = trawa;
			if(z == '#') plansza[i][j] = mur;
			if(z == '*') plansza[i][j] = jagoda;
			if(z == '@') plansza[i][j] = teleport;
			if(z == 'W') plansza[i][j] = wyjscie;
		}	
		getchar();
	}
	//~printf("WEJSCIE\n");
	//~for(int i = 0; i < n; i++) {
		//~for(int j = 0; j < n; j++) printf("%d",plansza[i][j]);
		//~printf("\n");
	//~}
}

void dfs(int x, int y, int energia) {
	
	if(x < 0 || y < 0 || x >= n || y >= n || plansza[x][y] == mur || energia < 0 || visited[x][y] == 1) //wyjscie poza plansze lub mur lub brak energii
		return;
	//~printf("inside dfs x y e %d %d %d\n",x,y,energia);
	if(plansza[x][y] == wyjscie) {
		//~printf("\nZNALEZIONE\n");
		if(ans < energia) ans = energia;
		return;
	}
	visited[x][y] = 1;
	if(plansza[x][y] == jagoda) 
		energia += 5;	
	if(plansza[x][y] == teleport) {
		for(int d = 1; d <= 3; d++) {
			dfs(x + d, y, energia);
			dfs(x - d, y, energia);
			dfs(x, y + d, energia);
			dfs(x, y - d, energia);
		}
	}
	if(plansza[x][y] == trawa || plansza[x][y] == jagoda) {
		dfs(x + 1, y, energia - 1);
		dfs(x - 1, y, energia - 1);
		dfs(x, y + 1, energia - 1);
		dfs(x, y - 1, energia - 1);
	}
	visited[x][y] = 0;
}

void solve() {
	dfs(xs,ys,e);
	if(ans == -1) printf("NIE");
	else printf("%d", ans);
}

int main() {
	wej();
	solve();
	
	return 0;
}
