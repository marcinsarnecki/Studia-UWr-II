#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

class graf{
private:
	std::map<int, std::vector<std::pair<int,int>>> m;// wierzcholek -> vector par <sasiad,waga>
	std::map<int, bool> visited;
public:
	void dodajWierzcholek(int v) {
		std::cout<<"Dodaje wierzcholek "<<v<<"\n";
		m[v] = std::vector<std::pair<int,int>>();
	}
	void usunWierzcholek(int v) {
		std::cout<<"Usuwam wierzcholek "<<v<<"\n";
		m.erase(v);
		for(auto &it: m) {
			std::cout<<"u="<<it.first<<"\n";
			if(it.second.size() == 0)
				continue;
			std::vector<std::pair<int,int>> &vec = it.second;
			vec.erase(std::remove_if(vec.begin(), vec.end(), [=](const std::pair<int,int>& pii) {return pii.first == v;}), vec.end()); 
		}
	}
	void dodajKrawedz(int v, int u, int c) {
		if(m.find(v) == m.end() || m.find(u) == m.end())
			throw std::invalid_argument("Podano nieistniejace wierzcholki!\n");
		std::cout<<"Dodaje krawedz pomiedzy wierzcholkami "<<v<<" i "<<u<<" o wadze "<<c<<"\n";
		m[v].push_back(std::make_pair(u, c));
		m[u].push_back(std::make_pair(v, c));
	}
	void usunKrawedz(int v, int u) {
		std::cout<<"Usuwam krawedz pomiedzy wierzcholkami "<<v<<" i "<<u<<"\n";
		auto itv = m.find(v);
		auto itu = m.find(u);
		std::vector<std::pair<int,int>> &vec1 = itv->second;
		vec1.erase(std::remove_if(vec1.begin(), vec1.end(), [=](const std::pair<int,int>& pii) {return pii.first == u;}), vec1.end());
		std::vector<std::pair<int,int>> &vec2 = itu->second;
		vec2.erase(std::remove_if(vec2.begin(), vec2.end(), [=](const std::pair<int,int>& pii) {return pii.first == v;}), vec2.end()); 
	}
	void dfs(int v) {
		//~ cout<<"dfs v="<<v<<"\n";
		visited[v] = true;
		std::vector<std::pair<int,int>> &vec = m[v];
		for(auto it: vec) {
			if(!visited[it.first])
				dfs(it.first);
		}
	}
	void sprawdzSciezka(int a, int b) {//czy z a moge isc do b
		if(m.find(a) == m.end() || m.find(b) == m.end())
			throw std::invalid_argument("Podano nieistniejace wierzcholki!\n");
		visited.clear();
		for(auto it: m)
			visited[it.first] = false;
		dfs(a);
		if(visited[b])
			std::cout<<"Istnieje sciezka pomiedzy "<<a<<" i "<<b<<"\n";
		else
			std::cout<<"Nie istnieje sciezka pomiedzy "<<a<<" i "<<b<<"\n";
	}
	void print() {
		std::cout<<"\nCaly graf:\n";
		for(auto &it: m) {
			std::cout<<it.first<<": ";
			for(auto p: it.second)
				std::cout<<"("<<p.first<<","<<p.second<<") ";
			std::cout<<"\n";
		}
		std::cout<<"\n";
	}
};


int main() {
	graf G;
	for(int i = 1; i <= 8; i++)
		G.dodajWierzcholek(i);
	G.dodajKrawedz(1, 2, 10);
	G.dodajKrawedz(1, 3, 5);
	G.dodajKrawedz(2, 3, 4);
	G.dodajKrawedz(1, 4, 3);
	G.dodajKrawedz(4, 5, 6);
	G.dodajKrawedz(5, 6, 7);
	G.dodajKrawedz(6, 7, 8);
	G.print();
	G.usunWierzcholek(1);
	G.usunKrawedz(4, 5);
	G.print();
	G.sprawdzSciezka(5, 7);
	G.sprawdzSciezka(2, 7);
	G.dodajKrawedz(3, 5, 2);
	G.sprawdzSciezka(2, 7);
	return 0;
}
