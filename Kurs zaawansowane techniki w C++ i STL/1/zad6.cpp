#include <iostream>
#include <iomanip>
#include <math.h>

const double d = 1.0e-9;

bool eq(double a, double b) {
    return abs(a-b) <= d;
}

void solve(double a, double b, double c) {
    std::cout<<"f(x) = "<<a<<"x^2 + "<<b<<"x + "<<c<<"\n";
    if(double delta = b*b - 4*a*c; eq(delta, 0.0)) {
        double x0 = -b / (2*a);
        std::cout<<"x0 = "<<x0<<"\n";
    }
    else if(delta > 0.0) {
        double dsqrt = sqrt(delta);
        double x0 = (-b - dsqrt) / (2*a), x1 = (-b + dsqrt) / (2*a);
        std::cout<<"x0, x1 = "<<x0<<", "<<x1<<"\n";
    }
    else if(delta < 0.0) {
        std::cout<<"delta < 0, brak rozwiazan rzeczywistych\n";
    }
}

int main() {
    std::cout<<std::fixed<<std::setprecision(2); //zaokraglenie do 2 miejsc po przecinku
    solve(2, 4, 2);
    solve(-4, 0, 10);
    solve(4, 3,2);
    return 0;
}
