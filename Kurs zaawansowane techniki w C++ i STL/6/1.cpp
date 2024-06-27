#include<bits/stdc++.h>

class person {
private:
		std::string name, surname;
		int age, weight;
		float height;
public:
		float bmi() const {
			return weight / (height * height);
		}
		int get_age() const { //settery i gettery
			return age;
		}
		void set_age(int new_age) {
			age = new_age;
		}
		int get_weight() const {
			return weight;  
		}
		void set_weight(int new_weight) {
			weight = new_weight;
		}
		float get_height() const{
			return height;
		}
		void set_height(float new_height) {
			height = new_height;
		}
		void print() {
			std::cout<<name<<" "<<surname<<", "<<age<<" years old, "<<floor(height)<<"."<<((int)(height * 100))%100<<"m "<<weight<<"kg\n";
		}
		person(std::string name_arg, std::string surname_arg, int age_arg, int weight_arg, float height_arg)
        : name(name_arg), surname(surname_arg), age(age_arg), weight(weight_arg), height(height_arg) {} 
};

int main() {
	std::deque<person> people = {
        person ("Sylwia", "Nowakowska", 32, 70, 1.78),
        person ("Ania", "Ostrowska",  33, 52, 1.68),
        person ("Mieczysław", "Pawłowski", 40, 120, 1.93),
        person ("Łukasz", "Jaworski", 32, 57, 1.63),
        person ("Cecylia", "Chmielewska", 32, 77, 1.75),
        person ("Jaromir", "Szczepański", 35, 77, 1.83),
        person ("Oskar", "Adamski", 26, 84, 1.88),
        person ("Wiktor", "Wieczorek", 43, 68, 1.73),
        person ("Borys", "Sobczak", 35, 52, 1.60),
        person ("Iwona", "Jabłońska", 39, 61, 1.73),
        person ("Dominika", "Szymańska", 43, 130, 1.91)
    };
    
    std::sort(people.begin(), people.end(), [](const person &a, const person &b) -> bool //sortowanie po bmi, comparator jako lambda
		{ return a.bmi() < b.bmi(); });
	std::cout<<"BMI sorted:\n";
	for(auto it: people)
		it.print();
	std::cout<<"\n";
    
    std::for_each(people.begin(), people.end(), [&](person &a) { //for each z lambdą modyfikującą
		a.set_weight(a.get_weight() * 0.9);
	});
	std::cout<<"After sports camp:\n";
    for(auto it: people)
		it.print();
	std::cout<<"\n";
	
	auto g = std::partition(people.begin(), people.end(), [](const person &a) -> bool { //iterator na granice
			return a.get_weight() > 100;
	});

    std::cout << ">100kg:\n";
    for (auto it = people.begin(); it != g; it++)
        it->print();
    std::cout<<"\n";

    std::cout << "<100kg:\n";
    for (auto it = g; it != people.end(); it++)
        it->print();
    std::cout<<"\n";
    
    std::nth_element(people.begin(), people.begin() + 5, people.end(), [](const person &a, const person &b) -> bool { return a.get_height() < b.get_height(); });
	std::cout<<"Median height: ";
	people[5].print();
	std::cout<<"\n";
	
    std::random_shuffle(people.begin(), people.begin() + 5);
    std::random_shuffle(people.begin() + 6, people.begin() + 11);
    std::cout<<"After two random shuffles:\n";
    for(auto it: people)
		it.print();
	std::cout<<"\n";
    
    auto itpair = std::minmax_element(people.begin(), people.end(), [](const person &a, const person &b) -> bool { return a.get_age() < b.get_age(); });
    std::cout<<"Youngest:\n";
    people[itpair.first - people.begin()].print();
    std::cout<<"\n";
    
    std::cout<<"Oldest:\n";
    people[itpair.second - people.begin()].print();
    std::cout<<"\n";
	return 0;
}
