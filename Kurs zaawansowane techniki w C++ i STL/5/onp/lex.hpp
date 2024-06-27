#pragma once
#include <variant>
#include <string>
#include <queue>
#include <variant>

enum class dzialanie : char {
    plus = '+',
    minus = '-',
    dziel = '/',
    razy = '*',
    pot = '^'
};

enum class nawias : char {
    lewy = '(',
    prawy = ')'
};

enum class lacznosc {//potegowanie ma inna laczosc
    lewa, prawa
};

using symbol = std::variant<dzialanie, nawias, int>;

auto przetworz(const std::string&)->std::queue<symbol>;

auto priorytet(dzialanie) -> int;

auto jaka_lacznosc(dzialanie)->lacznosc;