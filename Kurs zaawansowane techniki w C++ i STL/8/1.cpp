#include<iostream>
#include<complex>
#include<numeric>
#include<vector>

using namespace std;


complex<double> wartosc(vector<complex<double>> W, complex<double> x) { //wielomian W, wartosc dla podanego x
	return accumulate(W.begin(), W.end(), 
		complex<double>(0), //poczatek
		[&, p = complex<double>(1)] (auto s, auto w_i) mutable {
			s += w_i * p; //sumuje
			p *= x; //poteguje x
			return s;
		});
}


int main() {
	vector<complex<double>> w;
	w.push_back(complex<double>(1,1));
	w.push_back(complex<double>(8,-1));
	w.push_back(complex<double>(3,0));
	w.push_back(complex<double>(5,0));
	w.push_back(complex<double>(6,4));
	cout<<wartosc(w, 3);
	return 0;
}
