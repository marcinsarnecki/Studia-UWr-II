#include <iostream>

auto lucas_recursion(uint32_t n, uint64_t a, uint64_t b) {//rekurencja z pamietaniem obliczanych wartosci, bez pelnej rekurencji bo zlozonosc wykladnicza
    if(n == 0)
        return b;
    if(n == 1)
        return a;
    return lucas_recursion(n-1, a + b, a);
}

auto lucas(uint32_t n) {
    return lucas_recursion(n, 1, 2);
}



int main() {
    for(int i = 0; i <= 10; i++)
        std::cout<<"L"<<i<<" = "<<lucas(i)<<"\n";
    return 0;
}