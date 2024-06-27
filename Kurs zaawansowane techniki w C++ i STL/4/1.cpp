#include<bits/stdc++.h>
#include<iterator>
#include<functional>

using namespace std;


template<typename T>
class cmp {//klasa - funktor do wypisywania z danego przedzialu
public:
	function<void(T)> operator()(const T& a, const T& b) {
		return [&](const T &x) {//zwraca funkcje 
			if(a < x && x < b)
				cout<<x<<" ";
		};
	}
};

template<typename T>
class k_p_value {
	int k, p, idx = 0;
public:
	function<void(T)> operator()() {
		return [&](const T &x) {
			if(++idx < p)
				return;
			if((idx - p) % k == 0)
				cout<<x<<" ";
		};
	}
	k_p_value(int k1, int p1) {
		k = k1;
		p = p1;
	}
};

template <typename Ts>
auto find_minmax(const Ts& elements)
{
    auto min = elements.begin(), max = elements.begin(), iter = elements.begin();
    std::for_each(elements.begin(), elements.end(), [&](auto& elem) {
        if (elem < *min)
            min = iter;
        else if (*max < elem)
            max = iter;
        iter++;
    });
    return pair{min, max};
}

template<typename T>
class average_value{
	T current_sum = 0;
	double *ptr;
	int l = 0;
public:
	function<void(T)> operator()() {
		return [&](const T &x) {
			l++;
			current_sum += x;
			*ptr = (double) current_sum / l;
		};
	}
	average_value(double *ptr1) {
		ptr = ptr1;
	}
};

template <typename T>
auto all_elements_sum(T elements, typename T::value_type ans)
{
    std::for_each(elements.begin(), elements.end(), [&](auto& value) { ans += value; });
    return ans;
}


int main() {
	vector<double> v({1.0, 4.5, 3.324, 49.0, 14.0, 5.6, 8.53, 15.6, 54.0, 10.3, 34.5, 12.4, 4.5, 7.9, 24.21});
	list<string> l({"napis", "uniwersytet", "programowanie", "c++", "funktory", "abcdefg", "kompilator"});
	set<int> s({1, 6, 4, 3, 10, 15, 49, 23, 45, 123, 78, 83, 54, 33, 22, 41, 61, 72});
	
	cout<<"elementy z danego zakresu:\n\n";
	for_each(v.begin(), v.end(), cmp<double>()(4.0, 20.0));
	cout<<"\n";
	for_each(l.begin(), l.end(), cmp<string>()("dd", "rr"));
	cout<<"\n";
	for_each(s.begin(), s.end(), cmp<int>()(10, 50));
	cout<<"\n\n\n";
	
	cout<<"co k-ty element zaczynajac od p:\n\n";
	for_each(v.begin(), v.end(), k_p_value<double>(2, 5)());
	cout<<"\n";
	for_each(l.begin(), l.end(), k_p_value<string>(2, 2)());
	cout<<"\n";
	for_each(s.begin(), s.end(), k_p_value<int>(3, 2)());
	cout<<"\n\n\n";
	
	cout<<"srednie wartosci:\n\n";
	double vector_average = 0, set_average = 0;
	for_each(v.begin(), v.end(), average_value<double>(&vector_average)());
	for_each(s.begin(), s.end(), average_value<int>(&set_average)());
	cout<<"srednia vectora: "<<vector_average<<"\n";
	cout<<"srednia seta:    "<<set_average<<"\n";
	cout<<"\n\n";
	
	cout<<"miny maxy:\n\n";
	auto vpair = find_minmax<vector<double>>(v);
	auto lpair = find_minmax<list<string>>(l);
	auto spair = find_minmax<set<int>>(s);
	cout<<"vector: "<<*vpair.first<<" "<<*vpair.second<<"\n";
	cout<<"list:   "<<*lpair.first<<" "<<*lpair.second<<"\n";
	cout<<"set:    "<<*spair.first<<" "<<*spair.second<<"\n";
	
	cout<<"sumy:\n\n";
	auto vector_sum  = all_elements_sum<std::vector<double>>(v, 0.0);
    auto list_sum = all_elements_sum<std::list<std::string>>(l, std::string());
    auto set_sum  = all_elements_sum<std::set<int>>(s, 0);
	cout<<"vector: "<<vector_sum<<"\n";
	cout<<"list:   "<<list_sum<<"\n";
	cout<<"set:    "<<set_sum<<"\n";
	
	return 0;
}
