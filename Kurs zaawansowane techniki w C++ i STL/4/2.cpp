#include<bits/stdc++.h>

using namespace std;

template<typename F, typename G, typename H>
class compose_f_g_h {
	F f;
	G g;
	H h;
public:
	compose_f_g_h(F f1, G g1, H h1) : f(f1), g(g1), h(h1) {};//konstruktor, przypisuje funkcje z argumentow
	auto operator()(auto x, auto y) {
		return f(g(x), h(y));
	}
};


int square(int x) { return x * x; }
int add1(int x) { return x + 1; }
int add(int x, int y) { return x + y; }

int main() {
	auto c = compose_f_g_h(add, add1, square)(10, 10);
	cout<<c<<"\n";
	return 0;
}
