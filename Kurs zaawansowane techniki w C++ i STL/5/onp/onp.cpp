#include "onp.hpp"
#include <exception>
#include <iostream>



bool czy_zdjac(int p1, int p2, lacznosc l) {
    switch (l) {
    case lacznosc::lewa:
        return p2 >= p1;
    default:
        return p2 > p1;
    }
}

std::queue<symbol> onp(std::queue<symbol>&& symbole) {
    std::stack<symbol> stos;
    std::queue<symbol> wyjscie;

    while (!symbole.empty()) {
        auto symbol = symbole.front();
        symbole.pop();
        if (std::holds_alternative<int>(symbol)) { 
            wyjscie.push(symbol);
        }
        else if (std::holds_alternative<dzialanie>(symbol)) {
            auto op = std::get<dzialanie>(symbol);
            auto assoc = jaka_lacznosc(op);
            auto priority = priorytet(op);

            while (!stos.empty()) {
                if (!std::holds_alternative<dzialanie>(stos.top())) 
                    break;
                auto top_op = std::get<dzialanie>(stos.top());
                auto top_priority = priorytet(top_op);
                if (!czy_zdjac(priority, top_priority, assoc)) 
                    break;
                wyjscie.push(stos.top());
                stos.pop();
            }
            stos.push(symbol);
        }
        else {
            switch (std::get<nawias>(symbol)) {
            case nawias::prawy: {
                while (!stos.empty()) {
                    auto& top = stos.top();
                    if (std::holds_alternative<nawias>(top)) 
                        break;
                    wyjscie.push(top);
                    stos.pop();
                }
                if (stos.empty()) 
                    throw std::invalid_argument("Niedomkniete nawiasy!");
                stos.pop();
                break;
            }
            case nawias::lewy:
                stos.push(nawias::prawy);
                break;
            }
        }
    }

    while (!stos.empty()) {
        auto& top = stos.top();
        if (std::holds_alternative<nawias>(top)) 
            throw std::invalid_argument("Niedomkniete nawiasy!");
        wyjscie.push(top);
        stos.pop();
    }

    return wyjscie;
}
