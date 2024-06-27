#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define N 72
int tab[N][N], visited[N][N], rozmiar[N*N/2], idx, maksi, mini = N*N, id1, id2;

void dfs(int i, int j) {
	visited[i][j] = 1;
	tab[i][j] = idx;
	rozmiar[idx]++;
	if(visited[i-1][j] == 0 && tab[i-1][j] != 0) dfs(i-1,j);
	if(visited[i+1][j] == 0 && tab[i+1][j] != 0) dfs(i+1,j);
	if(visited[i][j-1] == 0 && tab[i][j-1] != 0) dfs(i,j-1);
	if(visited[i][j+1] == 0 && tab[i][j+1] != 0) dfs(i,j+1);
}

int main() {
	int n, m;
	scanf("%d%d", &m, &n);
	getchar();
	rep(j,0,m+1) visited[0][j] = visited[n+1][j] = 1;//brzegi dokola
	rep(i,0,n+1) visited[i][0] = visited[i][m+1] = 1;//planszy
	rep(i,1,n) {
		rep(j,1,m) {
			char z;
			scanf("%c", &z);
			if(z == '0') tab[i][j] = 0;
			if(z == 'x') tab[i][j] = 1;
		}
		getchar();
	}
	rep(i,1,n)
		rep(j,1,m)
			if(visited[i][j] == 0 && tab[i][j] != 0) {
				++idx;
				dfs(i,j);
			}
	printf("\nwynik:\n");
	rep(i,1,n) {
		rep(j,1,m) printf("%d",tab[i][j] % 10);
		printf("\n");
	}
	printf("\n");
	rep(i,1,idx) 
		if(maksi < rozmiar[i]) {
			maksi = rozmiar[i];
			id1 = i;
		}
	rep(i,1,idx)
		if(mini > rozmiar[i]) {
			mini = rozmiar[i];
			id2 = i;
		}
	printf("ilosc obszarow: %d\n", idx);
	printf("maksymalny obszar: id %d (wielkosc %d)\n", id1, maksi);
	printf("minimalny obszar: id %d (wielkosc %d)", id2, mini);
	return 0;
}
