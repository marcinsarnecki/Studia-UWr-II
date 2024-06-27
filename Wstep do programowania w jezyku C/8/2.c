#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)

typedef struct node {
	int key, visited;
	struct node *left, *right, *parent;
}node;

node* newNode(int value, node *parent) 
{
    node* temp = (node*)malloc(sizeof(node)); 
    temp->key = value; 
    temp->left = temp->right = NULL;
    temp->parent = parent; 
    temp->visited = 0;
    return temp; 
}

char input[35000000];
int idx;
int inputNum[6000000], ndx;
node* ptr_tab[6000000];
int pdx;

int szukany;
node* ptr1;
int ans;

void find(node* v) {
	v->visited = 0;
	if(v->left != NULL) find(v->left);
	if(v->key == szukany) {
		ptr1 = v;
	}
	//~printf("%d\n", v->key);
	if(v->right != NULL) find(v->right);
}

void wej() {
	while(1) {
		char c = getchar();
		if(c == EOF) 
			break;
		input[idx++] = c;
	}
	int current = 0, k = 1;
	char z;
	repv(i,idx-2,0) {
		z = input[i];
		if(z == '-') current *= (-1);
		if(z >= '0' && z <= '9') {
			current += (int)(z-48) * k;
			k *= 10;
		}
		if(z == ' ' || z == '\n' || i == 0) {	
			inputNum[ndx++] = current;
			current = 0;
			k = 1;
		}
	}
	for(int i = 0, j = ndx - 1; i < j; i++, j--) {
		inputNum[i] = inputNum[i] ^ inputNum[j];
		inputNum[j] = inputNum[j] ^ inputNum[i];
		inputNum[i] = inputNum[i] ^ inputNum[j];
	}
}

node* make_tree(node* tree) {
	idx = 0;//po inputNum
	tree = newNode(inputNum[idx++], NULL);
	ptr_tab[pdx++] = tree;
	int j = 0;//po ptr_tab
	while(j < pdx) {
		int num1 = inputNum[idx++];
		int num2 = inputNum[idx++];
		if(num1 == -1) 
			ptr_tab[j]->left = NULL;
		else {
			ptr_tab[j]->left = newNode(num1, ptr_tab[j]);
			ptr_tab[pdx++] = ptr_tab[j]->left;
		}
		if(num2 == -1) 
			ptr_tab[j]->right = NULL;
		else {
			ptr_tab[j]->right = newNode(num2, ptr_tab[j]);
			ptr_tab[pdx++] = ptr_tab[j]->right;
		}
		j++;
	}
	return tree;
}

void dfs(node* v, int d) {
	//~printf("inside dfs v=%d\n",v->key);
	v->visited = 1;
	if(v->key == szukany) ans = d;
	if(v->parent != NULL && v->parent->visited == 0) dfs(v->parent, d+1);
	if(v->left != NULL && v->left->visited == 0) dfs(v->left, d+1);
	if(v->right != NULL && v->right->visited == 0) dfs(v->right, d+1);
}

void solve(node* tree) {
	while(idx < ndx) {
		int a = inputNum[idx++];
		int b = inputNum[idx++];
		//~printf("a=%d b=%d\n", a, b);
		szukany = a;
		find(tree);
		szukany = b;
		if(ptr1 != NULL) {
			//~printf("wlaczam dfsa!!!\n");
			dfs(ptr1, 0);
		}
		printf("%d ",ans);
	}
}

int main() {
	wej();
	node* tree = NULL;
	tree = make_tree(tree);
	solve(tree);
	return 0;
}

