#include <iostream>
#include <string>

enum class name : uint16_t 
{
    Michal, Anna, Artur, Magdalena, Jacek, Marta
};

void f(std::string text, name person) {
    std::string s;
    switch (person)
    {
    case name::Michal: {s = "Michal"; break;}
    case name::Anna: {s = "Anna"; break;}
    case name::Artur: {s = "Artur"; break;}
    case name::Magdalena: {s = "Magdalena"; break;}
    case name::Jacek: {s = "Jacek"; break;}
    case name::Marta: {s = "Marta"; break;}
    default: s = "";
    }
    std::cout<<text<<" "<<s<<"\n";
}

int main() {
    f("Witamy we Wroclawiu,",name::Magdalena);
    return 0;
}