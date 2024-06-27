#include <iostream>
#include <complex>
using namespace std;

const double euler_mascheroni = 0.5772156649;

std::complex<double> gamma (std::complex<double> z, int ile) {
    complex<double> ans = 1.0 / z;
    for (int i = 1; i <= ile; i++) 
        ans *= std::pow(1.0 + 1.0 / static_cast<double>(i), z) / (1.0 + z / static_cast<double>(i)); //aplikuje wzor
    return ans;
}

std::complex<double> odwrotna_gamma (std::complex<double> z, int ile) {
    complex<double> result = z * exp(euler_mascheroni * z);
    for (int i = 1; i <= ile; i++)
        result *= (1.0 + z / static_cast<double>(i)) * exp(z / static_cast<double>(i)); //aplikuje wzor
    return result;
}

int main() {
    double rzeczywista, urojona;
    int ile;
    cin>>rzeczywista>>urojona>>ile;
    complex<double> z(rzeczywista, urojona);
    cout << "gamma(z)   = " << gamma(z, ile) << endl;
    cout << "1/gamma(z) = " << odwrotna_gamma(z, ile) << endl;
}
