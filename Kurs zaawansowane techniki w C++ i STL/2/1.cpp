#include <iostream>
#include <memory>

class MyClass{
	uint64_t licznik = 1;
public:
	~MyClass() {
		std::cerr<<"Wartosc licznika: "<<licznik<<std::endl;
	}
	void dodaj(uint64_t x) {
		licznik += x;
	}
	friend std::ostream& operator<<(std::ostream& output, const MyClass& obj) {
		output<<obj.licznik;
		return output;
	} 
};

void f1(std::unique_ptr<MyClass[]> t, uint64_t n, uint64_t i, uint64_t m) {
	if(i > m)
		return;
	for(uint64_t j = 0; j < n; j++)
		if(rand()%2==1)
			t[j].dodaj(i);
	f1(std::move(t), n, i+1, m);	
}

int main() {
	uint64_t n = 3, m = 3;
	std::unique_ptr<MyClass[]> tab(new MyClass[n]);
	f1(std::move(tab), n, 1, m);
	return 0;
}
