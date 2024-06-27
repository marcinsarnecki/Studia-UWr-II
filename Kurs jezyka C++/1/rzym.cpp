#include<bits/stdc++.h> //Marcin Sarnecki 323034
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const vector<pair<int, string>> rzym = {	
	{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100,"C"}, {90, "XC"}, {50,"L"}, {40, "XL"}, {10, "X"}, {9, "IX"} , {5, "V"}, {4, "IV"}, {1, "I"}
};

string bin2Rzym(int x) {
	string ans;
	while(x) 
		rep(i,0,12) {
			if(rzym[i].f <= x) {
				x -= rzym[i].f;
				ans += rzym[i].s;
				break;
			}
		}
	return ans;
}

int main(int argc, char **argv) {	
	rep(i,1,argc-1) {
		int num = atoi(argv[i]);
		if(num >= 1 && num <= 3999)	
			cout<<bin2Rzym(num)<<"\n";
		else
			clog<<"Liczba spoza zakresu!\n";
	}
	return 0;
}