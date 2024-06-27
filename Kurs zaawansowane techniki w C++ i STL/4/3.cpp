#include<bits/stdc++.h>

using namespace std;

int square(int x) 
{ 
    x = x * x;
    cout << "Funkcja x=x*x " << x << endl;
    return x;
}

int increment(int x)
{ 
	x = x + 1;
	cout<<"Funkcja x=x+1 "<<x<<"\n";
    return x;
}

int decrement(int x)
{ 
    x = x - 1;
    cout<<"Funkcja x=x-1 "<<x<<"\n"; 
    return x;
}

int main() 
{
    auto po_kolei = [](auto f, auto g) {
        return [=](auto x) {
            f(x);
            g(x);
        };
    };

    cout << "kwadrat, +1 dla x=1" << endl;
    po_kolei(square, increment)(1);
	cout<<"\n";
	
	
    cout << "+1, kwadrat dla x=2" << endl;
    po_kolei(increment, square)(2); 
	cout<<"\n";

    cout << "kwadrat, +1, -1 dla x=3" << endl;
    po_kolei(po_kolei(square, increment), decrement)(3); 
	cout<<"\n";

    cout << "-1, kwadrat, +1 dla x=4" << endl;
    po_kolei(decrement, po_kolei(square, increment))(4); 
}
