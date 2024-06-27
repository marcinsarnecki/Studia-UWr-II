#include<bits/stdc++.h>

int main() {
	float denormMinFloat = std::numeric_limits<float>::denorm_min();
    double denormMinDouble = std::numeric_limits<double>::denorm_min();
    float maxFloat = std::numeric_limits<float>::max();
    double maxDouble = std::numeric_limits<double>::max();
    float epsilonFloat = std::numeric_limits<float>::epsilon();
    double epsilonDouble = std::numeric_limits<double>::epsilon();
    std::cout << "Smallest float > 0:	" << denormMinFloat << std::endl;
    std::cout << "Smallest double > 0:	" << denormMinDouble << std::endl;
    std::cout << "Maximum float:		" << maxFloat << std::endl;    
    std::cout << "Maximum double:		" << maxDouble << std::endl;
    std::cout << "Epsilon float:		" << epsilonFloat << std::endl;
    std::cout << "Epsilon double:		" << epsilonDouble << std::endl;
	return 0;
}
