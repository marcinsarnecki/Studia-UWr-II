#include <iostream>
#include <string>

struct date{
    int d, m, y;
};

date string_to_date(std::string s) {
    std::string delimiter = "-";
    size_t pos = 0;
    int idx = 0;
    int data[3]{0, 0, 0};
    while ((pos = s.find(delimiter)) != std::string::npos) {
        data[idx++] = stoi(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    data[idx++] = stoi(s);
    return date{data[0], data[1], data[2]};
}

void print_date(date a){
    std::string m = "";
    switch(a.m) {
        case 1: {m = "stycznia"; break;}
        case 2: {m = "lutego"; break;}
        case 3: {m = "marca"; break;}
        case 4: {m = "kwietnia"; break;}
        case 5: {m = "maja"; break;}
        case 6: {m = "czerwca"; break;}
        case 7: {m = "lipca"; break;}
        case 8: {m = "sierpnia"; break;}
        case 9: {m = "wrzesnia"; break;}
        case 10: {m = "pazdziernika"; break;}
        case 11: {m = "listopada"; break;}
        case 12: {m = "grudnia"; break;}
    }
    std::cout<<a.d<<" "<<m<<" "<<a.y<<"\n";
}

int main() {
    std::string s;
    std::cout<<"Podaj date w formacie dd-mm-yyyy\n";
    std::cin>>s;
    print_date(string_to_date(s));
    return 0;
}