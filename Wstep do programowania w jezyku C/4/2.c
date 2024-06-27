#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


char current[128];
char ans[128];
int ansLen, currentLen;
int ansState = -1; //-1 brak jakiejkolwiek odpowiedzi, 2 - dodatnia, 1 - ujemna
int state;// 0 oznacz nic, 1 oznacza wpisywana ujemna, 2 oznacza wpisywana dodatnia

void compare(int info, int len) {
//	printf("porownuje len=%d info=%d\n", len, info);
	if(ansState == -1) {
		ansLen = len;
		ansState = info;
		for(int i = 0; i < len; i++) ans[i] = current[i];
	}
	if(ansState == 2) {
		if(info == 2) {
			//porownanie 2 dodatnich
			if(ansLen < len)
				return;
			if(ansLen > len) {
				for(int i = 0; i < len; i++) ans[i] = current[i];
				ansLen = len;
			}
			if(ansLen == len) {
				//porownanie 2 dodatnich o tej samej dlugosci
				for(int i = 0; i < len; i++)
					if(ans[i] < current[i])
						return;
				for(int i = 0; i < len; i++) ans[i] = current[i];	
			}
		}
		if(info == 1) { //ans bylo dodatnie a znaleziono ujemna liczbe
			ansState = info;
			ansLen = len;
			for(int i = 0; i < len; i++) ans[i] = current[i];
		}
	}
	else if(ansState == 1) {
		if(info == 2) //ujemnej z dodatnia nie ma co porownywac
			return;
		if(info == 1) {
			//porownanie 2 ujemnych
			if(ansLen > len)
				return;
			if(ansLen < len) {
				for(int i = 0; i < len; i++) ans[i] = current[i];
				ansLen = len;
			}
			if(ansLen == len) {
				//porownanie 2 ujemnych o tej samej dlugosci wiec bierzemy te wieksza
				for(int i = 0; i < len; i++)
					if(ans[i] > current[i])
						return;
				for(int i = 0; i < len; i++) ans[i] = current[i];
			}
		}
		
	}
	
}

bool czyCyfra(char z) {
	return (z >= '0' && z <= '9');
}

int main() {
	while(1) {
		int c = getchar();
		if(c == EOF) 
			break;
		if(c == '-') {
			state = 1;
			currentLen = 0;
		}
		else if(czyCyfra(c) == 0) {
			if(currentLen > 0) compare(state, currentLen);
			currentLen = 0;
			state = 0;
		}
		else if(czyCyfra(c)) {
			if(state == 0) {
				state = 2;
				current[currentLen++] = c;
			}
			else if(state == 1) {
				current[currentLen++] = c;
			}
			else if(state == 2) {
				current[currentLen++] = c;
			}
		}
		
	}
	if(currentLen > 0) compare(state, currentLen);
	if(ansState == 1) printf("-");
	for(int i = 0; i < ansLen; i++) printf("%c", ans[i]);
	return 0;
}
