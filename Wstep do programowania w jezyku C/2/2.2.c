#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main() {
	int litery = 0, len = 0, cyfry = 0, whitespaces = 0, wyrazy = 0, ilesamogloski = 0, ilespolgloski = 0, duze = 0, male = 0, ileprzestankowe = 0;
	bool wyrazyState = false;
	int samogloski[]={'a','e','i','o','u','y'};
	int przestankowe[]={',', '.', ':', '!', '?'};
	int dif = 'a' - 'A';
	while(1) {
		int c = getchar();
		if(c == EOF || c == '\n') 
			break;
		len++;														//sama dlugosc
		
		if(c >= '0' && c <= '9') cyfry++;							//cyfry
		
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {		//cala obsluga liter
			litery++;
			if(!wyrazyState) wyrazy++;
			wyrazyState = true;										//ile wyrazow
			
			bool czySamogloska = false;								//samogloski spolgloski
			for(int i = 0; i < sizeof(samogloski) / sizeof(int); i++) 
				if(c == samogloski[i] || c == samogloski[i] - dif) {
					ilesamogloski++;
					czySamogloska = true;
				}
			if(!czySamogloska) ilespolgloski++;						
			
			if(c >= 'a' && c <= 'z') male++;						//male duze
								else duze++;
		}
		else wyrazyState = false;
		
		if(c <= ' ') whitespaces++;									//biale spacje, przestankowe
		for(int i = 0; i < sizeof(przestankowe) / sizeof(int); i++) 
			if(c == przestankowe[i]) ileprzestankowe++;
	}
	printf("znaki: %d\n", len);
	printf("litery: %d\n", litery);
	printf("cyfry: %d\n", cyfry);
	printf("biale spacje: %d\n", whitespaces);
	printf("wyrazy: %d\n", wyrazy);
	printf("samogloski: %d\n", ilesamogloski);
	printf("spolgloski: %d\n", ilespolgloski);
	printf("duze: %d\n", duze);
	printf("male: %d\n", male);
	printf("przestankowe: %d\n", ileprzestankowe);
	
	return 0;
}
