#include<bits/stdc++.h>
#include<ratio>

template<int n>
struct harmonic : public std::ratio_add<std::ratio<1,n>, harmonic<n-1>> {};

template<>
struct harmonic<1> : public std::ratio<1,1> {};

int main() {
	const int i = 46;
	std::cout<<"dla i="<<i<<": "<<harmonic<i>::num<<" / "<<harmonic<i>::den<<std::endl;
	std::cout<< "~ "<<(double)harmonic<i>::num / harmonic<i>::den<<std::endl;
	
	return 0;
}
