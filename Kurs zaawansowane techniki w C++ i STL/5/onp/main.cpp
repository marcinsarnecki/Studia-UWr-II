#include <iostream>
#include <sstream>
#include "onp.hpp"
//4+5*(1+1)/(5+5)
//4 5 1 1 + * 5 5 + / +

//4*3+1*3
//4 3 * 1 3 * +

int main(int argc, char* argv[]) {
    std::queue<symbol> symbole;
    std::string wejscie;
    std::getline(std::cin, wejscie);
    try {
        symbole = przetworz(wejscie);
    }
    catch (std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    std::queue<symbol> onp_wynik;
    try {
        onp_wynik = onp(std::move(symbole));
    }
    catch (std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    std::cout << "Odwrotna Notacja Polska:\n";
    while (!onp_wynik.empty()) {
        auto symbol = onp_wynik.front();

        if (std::holds_alternative<int>(symbol))//liczba
            std::cout << std::get<int>(symbol);
        else if (std::holds_alternative<nawias>(symbol)) 
            std::cout << static_cast<char>(std::get<nawias>(symbol));//zrzutowanie na chara
        else 
            std::cout << static_cast<char>(std::get<dzialanie>(symbol));

        std::cout << ' ';

        onp_wynik.pop();
    }
    std::cout << std::endl;
    return 0;
}
