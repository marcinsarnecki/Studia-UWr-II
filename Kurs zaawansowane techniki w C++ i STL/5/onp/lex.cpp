#include "lex.hpp"
#include <optional>
#include <exception>
#include <stdexcept>


bool is_valid_op_token(char c) {
    switch (c) {
        case static_cast<char>(dzialanie::plus) :
            case static_cast<char>(dzialanie::minus) :
            case static_cast<char>(dzialanie::dziel) :
            case static_cast<char>(dzialanie::razy) :
            case static_cast<char>(dzialanie::pot) :
            return true;
            default:
                return false;
    }
}

bool is_valid_bracket(char c)  {
    return c == static_cast<char>(nawias::lewy) ||
        c == static_cast<char>(nawias::prawy);
}

std::optional<symbol> nastepny_symbol(std::string& str) {
    if (str.empty()) 
        return {};
    while (str.front() == ' ')//wywalam spacje jesli sa na poczatku
        str.erase(1, 0);
    if (std::isdigit(str.front())) {
        int liczba = str[0] - '0';
        str.erase(0, 1);
        while (!str.empty() && std::isdigit(str.front())) {
            liczba = liczba * 10 + (str.front() - '0');
            str.erase(0, 1);
        }
        return liczba;
    }
    char c = str.front();
    str.erase(0, 1);

    if (is_valid_op_token(c)) 
        return dzialanie(c);
    if (is_valid_bracket(c)) 
        return nawias(c);
    throw std::invalid_argument("Nieprawidlowy znak w wyrazeniu arytmetycznym!");
}


std::queue<symbol> przetworz(const std::string& str) {
    std::string temp = str;
    std::queue<symbol> symbole;
    std::optional<symbol> symbol = {};
    while ((symbol = nastepny_symbol(temp)).has_value()) {
        symbole.push(*symbol);
    }

    return symbole;
}


auto priorytet(dzialanie d) -> int {
    switch (d) {
    case dzialanie::plus:
    case dzialanie::minus:
        return 0;
    case dzialanie::dziel:
    case dzialanie::razy:
        return 1;
    case dzialanie::pot:
        return 2;
    }
    throw std::invalid_argument("Nieprawidlowy operator!");
}


auto jaka_lacznosc(dzialanie d) -> lacznosc {
    switch (d) {
    case dzialanie::pot:
        return lacznosc::prawa;
    default:
        return lacznosc::lewa;
    }
}
