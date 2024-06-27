#include<bits/stdc++.h>

typedef long long int ll;

int main() {
	ll minValue = std::numeric_limits<ll>::min();
	ll maxValue = std::numeric_limits<ll>::max();
	int bits = sizeof(ll) * 8, digits = 0;
	ll temp = maxValue;
	while(temp > 0) {
		temp /= 10;
		digits++;
	}
	std::cout<<"Max value: "<<maxValue<<"\n";
	std::cout<<"Min value: "<<minValue<<"\n";
	std::cout<<"Bits used: "<<bits<<"\n";
	std::cout<<"Digits:    "<<digits<<"\n";
	return 0;
}
