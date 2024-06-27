#include <bits/stdc++.h>

template <typename From, typename To>
void moveFromTo(From& from, To& to, std::false_type) //referencja
{
    if (std::is_convertible<From, To>::value)
    {
        to = static_cast<To&&>(std::move(from));
        std::cout << "Przenosze przez referencje" << std::endl;
    }
    else  
        std::cout << "Brak mozliwosci konwersji" << std::endl;
}

template <typename From, typename To>
void moveFromTo(From from, To& to, std::true_type) //ze wskaznika
{
    if (std::is_convertible<typename std::remove_pointer<From>::type, To>::value) //czy jak wartosc spod *wskaznik moge przeniesc do 'to'
    {
        to = (To&&)(std::move(*from));
        std::cout << "Przenosze wskaznik" << std::endl;
    }
    else  
        std::cout << "Brak mozliwosci konwersji" << std::endl;
}

template <typename From, typename To>
void moveFromTo(From from, To& to)
{
    moveFromTo(from, to, std::is_pointer<From>());//w zaleznosci czy From jest pointerem zostanie wywolana wlasciwa funkcja
}

int main()
{
    // bez wskaznikow
    std::string s1 = "napis 1", s2 = "napis 2";
    moveFromTo(s1, s2);
    std::cout << "wyswietlam zawartosc napisu 2: "<<s2 << std::endl;
    // wskazniki
    std::string s3  = "napis 3";
    std::string *s4 = new std::string("napis 4 utworzony z wskaznikiem");
    moveFromTo(s4, s3);
    std::cout << "wyswietlam zawartosc napisu 3: "<<s3 << std::endl;
    delete s4;
}
