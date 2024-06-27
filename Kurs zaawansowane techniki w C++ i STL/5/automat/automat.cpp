#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Stan {//wierzcholek ze skierowanymi krawedziami w grafie stanow
private:
    map<int, int> cele;//krawedz -> stan

public:
    int wykonajRuch(int krawedz) {
        if (cele.find(krawedz) == cele.end()) {
            throw invalid_argument("No " + to_string(krawedz));
        }

        return cele[krawedz];
    }

    void dodajKrawedz(int stan, int krawedz) {
        cele[krawedz] = stan;
    }
};

class Automat {//automat (graf stanow)
private:
    map<int, Stan> stany; //id stanu -> stan
    int aktualnyStan;
    void wykonajRuch(int k) {
        this->aktualnyStan = stany[this->aktualnyStan].wykonajRuch(k);
    }
public:
    Automat() : aktualnyStan(0) {};
    Automat(int curr) : aktualnyStan(curr) {};
    void dodajStan(int id) {
        stany[id] = Stan();
    }
    void dodajKrawedz(int id_from, int id_to, int edge_label) {
        auto it = stany.find(id_from);
        if (it == stany.end()) throw invalid_argument("Proba dodania krawedzi do nieistniejacego stanu!");
        it->second.dodajKrawedz(id_to, edge_label);
    }
    void wykonaj(string moves) {
        for (char m : moves) {
            wykonajRuch(m - '0');
        }
    }
    int stan() {
        return this->aktualnyStan;
    }
    void ustawStan(int st) {
        this->aktualnyStan = st;
    }
};

int main(int argc, char** argv) {

    Automat parzystoscJedynek(0);
    parzystoscJedynek.dodajStan(0);
    parzystoscJedynek.dodajStan(1);
    parzystoscJedynek.dodajKrawedz(0, 1, 1);
    parzystoscJedynek.dodajKrawedz(1, 0, 1);
    parzystoscJedynek.dodajKrawedz(0, 0, 0);
    parzystoscJedynek.dodajKrawedz(1, 1, 0);

    parzystoscJedynek.wykonaj(string(argv[1]));
    cout << "Automat: parzystoscJedynek Argument: " <<string(argv[1]) << "  wynik: " << parzystoscJedynek.stan() << endl;

    Automat podzielnosc3(0);
    podzielnosc3.dodajStan(0);//3 stany reszty z dzielenia przez 3
    podzielnosc3.dodajStan(1);
    podzielnosc3.dodajStan(2);
    podzielnosc3.dodajKrawedz(0, 0, 0);//od kazdego stanu dla kazdej nastepnej liczby w ktorym stanie sie znajdziemy
    podzielnosc3.dodajKrawedz(0, 1, 1);
    podzielnosc3.dodajKrawedz(0, 2, 2);
    podzielnosc3.dodajKrawedz(0, 0, 3);
    podzielnosc3.dodajKrawedz(0, 1, 4);
    podzielnosc3.dodajKrawedz(0, 2, 5);
    podzielnosc3.dodajKrawedz(0, 0, 6);
    podzielnosc3.dodajKrawedz(0, 1, 7);
    podzielnosc3.dodajKrawedz(0, 2, 8);
    podzielnosc3.dodajKrawedz(0, 0, 9);
    podzielnosc3.dodajKrawedz(1, 1, 0);//od stanu 1
    podzielnosc3.dodajKrawedz(1, 2, 1);
    podzielnosc3.dodajKrawedz(1, 0, 2);
    podzielnosc3.dodajKrawedz(1, 1, 3);
    podzielnosc3.dodajKrawedz(1, 2, 4);
    podzielnosc3.dodajKrawedz(1, 0, 5);
    podzielnosc3.dodajKrawedz(1, 1, 6);
    podzielnosc3.dodajKrawedz(1, 2, 7);
    podzielnosc3.dodajKrawedz(1, 0, 8);
    podzielnosc3.dodajKrawedz(2, 2, 0);//od stanu 2
    podzielnosc3.dodajKrawedz(2, 0, 1);
    podzielnosc3.dodajKrawedz(2, 1, 2);
    podzielnosc3.dodajKrawedz(2, 2, 3);
    podzielnosc3.dodajKrawedz(2, 0, 4);
    podzielnosc3.dodajKrawedz(2, 1, 5);
    podzielnosc3.dodajKrawedz(2, 2, 6);
    podzielnosc3.dodajKrawedz(2, 0, 7);
    podzielnosc3.dodajKrawedz(2, 1, 8);
    podzielnosc3.dodajKrawedz(2, 2, 9);

    podzielnosc3.wykonaj(string(argv[2]));
    cout << "Automat: podzielnosc3	Argument: " << string(argv[2]) << "  wynik: " << podzielnosc3.stan() << endl;
    return 0;
}

