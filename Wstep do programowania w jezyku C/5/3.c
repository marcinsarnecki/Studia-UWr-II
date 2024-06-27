#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>//NEVER EVER TOUCH/READ THIS CODE AGAIN
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define N 257
int nsize, q;
char tab[N][N], pom[N][N];
char wej[10];

void AxialTwist(int log, int a, int b, int n) {
	a++, b++;
	int k = nsize / (1<<log);//KAFELEK
	a = k * (a-1) + 1;//od teraz prawidlowe moje indeksy, one sa zawsze + 
	b = (b * k);
	if(n < 0) {//w kolumnach
		n = abs(n);//w kierunku mniejszych indeksow
		int shift = (n * k) % nsize;
		rep(j,a,b)
			rep(i,1,nsize)
				pom[i][j] = tab[i][j];
		rep(j,a,b)
			rep(i,1,nsize)
				tab[i][j] = pom[(i+shift) > nsize ? i+shift - nsize : i+shift][j];
	}
	else {//w wierszach
		int shift = (n * k) % nsize;
		rep(i,a,b)
			rep(j,1,nsize)
				pom[i][j] = tab[i][j];
		rep(i,a,b)
			rep(j,1,nsize) 
				tab[i][j] = pom[i][(j+shift) > nsize ? j+shift - nsize : j+shift];
	}
}
void wyswietl() {
	rep(i,1,nsize) {
		rep(j,1,nsize) printf("%c",tab[i][j]);
		printf("\n");
	}
}
void Przekatna(int id, int k, int n) {
	int l = abs(id);
//	printf("zaczynam przekatna id=%d k=%d n=%d\n",id,k,n);
	if(id < 0) {
		rep(idx,0,(nsize/k)-l-1) {
			rep(i,1,k) {
				rep(j,1,k) {
					int x = (i + k * (l+idx)), y = (j + k * idx);
					pom[x][y] = tab[x][y];
					//~printf("mhmmm %d %d\n",x,y);
				}
			}
					
		}
		rep(idx,0,(nsize/k)-l-1) {
			int newid = idx + n > (nsize/k) - l - 1 ? (idx + n) % ((nsize/k) - l) : idx + n;
			rep(i,1,k)
				rep(j,1,k) {
					int x = i + k * (l+idx), y = (j + k * idx);
					int x2 = i + k * (l+newid), y2 = (j + k * newid);
					tab[x][y] = pom[x2][y2];
				}
		}
	}
	if(id >= 0) {
		rep(idx,0,(nsize/k)-l-1) {
			rep(i,1,k)
				rep(j,1,k) {
					int x = (i + k * idx), y = (j + k*(l+idx));
					pom[x][y] = tab[x][y];
					//~printf("mhmmm %d %d\n",x,y);
				}	
		}
		rep(idx,0,(nsize/k)-l-1) {
			int newid = idx + n > (nsize/k) - l - 1 ? (idx + n) % ((nsize/k) - l) : idx + n;
			//~printf("idx=%d newid=%d\n",idx,newid);
			rep(i,1,k)
				rep(j,1,k) {
					int x = (i + k * idx), y = (j + k*(l+idx));
					int x2 = (i + k * (newid)), y2 = (j + k*(l+newid));
					tab[x][y] = pom[x2][y2];
				}
		}
		
	}
}

void DiagonalTwist(int log, int a, int b, int n) {
	int k = nsize / (1<<log);//KAFELEK
	rep(i,a,b) {
	//	printf("jestem w i=%d\n",i);
		//if(i >= (nsize / k) || i <= -(nsize/k)) continue;
		Przekatna(i,k,n);
	}
}

int main() {//w diagonal twist 1 8 15 ... nie dziala
	scanf("[lg2img: %d][numTss: %d]",&nsize,&q);
	nsize = (1<<nsize);
	rep(i,1,nsize) {
		rep(j,1,nsize) {
			scanf("%c",&(tab[i][j]));
			if(tab[i][j] == '\n') j--;
		}
		getchar();
	}
	rep(i,1,q) { 
		scanf("%s", wej);
		int log, a, b, n;
		scanf("%d [%d %d] %d",&log,&a,&b,&n);
		if(a > b) {
			int c = a;
			a = b;
			b = c;
		}
		if(log == 0)
			continue;
		if((1<<log) > nsize) 
			continue;
		if(wej[0] == 'A')
			AxialTwist(log,a,b,n);
		if(wej[0] == 'D')
			DiagonalTwist(log,a,b,n);
	}
	wyswietl();
	return 0;
}
