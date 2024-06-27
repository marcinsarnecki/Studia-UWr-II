#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define INF -1e9

typedef struct node {
	int key;
	struct node *left, *right;
}WEZEL;

WEZEL* newNode(int value) 
{
    WEZEL* temp = (WEZEL*)malloc(sizeof(WEZEL)); 
    temp->key = value; 
    temp->left = temp->right = NULL;
    return temp; 
}

WEZEL* insert(WEZEL* v, int value) {
	if(v == NULL) 
		return newNode(value);
	if(v->key < value)
		v->right = insert(v->right, value);
	else if(v->key > value)
		v->left = insert(v->left, value);
	return v;
}

int szukaj(WEZEL* v, int value) {
	if(v == NULL)
		return 2*INF;
	if(v->key == value)
		return 1;
	if(v->key < value)
		return szukaj(v->right, value) + 1;
	else if(v->key > value)
		return szukaj(v->left, value) + 1;
}


int main() {
	WEZEL* root = NULL;
	int n, q;
	scanf("%d%d", &n, &q);
	rep(i,1,n) {
		int wa;
		scanf("%d", &wa);
		if(i == 1)
			root = insert(root, wa);
		else
			insert(root, wa);
	}
	rep(i,1,q) {
		int v;
		scanf("%d", &v);
		int d = szukaj(root, v);
		if(d < INF) 
			printf("glebokosc wierzcholka %d wynosi -1\n", v);
		else 
			printf("glebokosc wierzcholka %d wynosi %d\n", v, d);
	}
	return 0;
}
