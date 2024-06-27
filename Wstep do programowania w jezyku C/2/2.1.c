#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int main() {
	int i, count_d=0, count_m=0, count_c=0;
	char tab[10];
	printf("wprowadz 10 znakow:\n");
	for(i=0;i<10;i++)
    {
        scanf("%c", &tab[i]);
        getchar();
        if(tab[i] >= 97)
        {
            count_m++;
        }
        else if(tab[i] >= 65)
        {
            count_d++;
        }else if(tab[i] >= 48)
        {
            count_c++;
        }else
        break;
    }
    printf("Wpisales kolejno: \n %d malych liter \n %d duzych liter \n %d cyfr", count_m, count_d, count_c);
    return 0;
}
