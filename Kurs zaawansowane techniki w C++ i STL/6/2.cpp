#include <bits/stdc++.h>

enum class quarter{ first, second, third, fourth, none };

class point {
private:
    int x, y, r, g, b;
    std::string name;
public:
    point (int x_arg, int y_arg, int r_arg, int g_arg, int b_arg, const std::string& name_arg)
        : x(x_arg), y(y_arg), r(r_arg), g(g_arg), b(b_arg), name(name_arg) {}
    int get_x() const { 
		return x; 
	}
    int get_y() const { 
		return y; 
	}
    int get_r() const { 
		return r; 
	}  
    int get_g() const { 
		return g; 
	}  
    int get_b() const { 
		return b; 
	}  
    void set_x(int value){ 
		x = value;
	}
    void set_y(int value){
		y = value; 
	}
    void set_r(int value){
		r = value;
	}
    void set_g(int value){
		g = value;
	}
    void set_b(int value){
		b = value;
	}
    std::string get_name() const {
		return name;
	}
    void set_name(std::string value) {
		name = value;
	}
    double brightness() const {
        return 0.3 * r + 0.59 * g + 0.11 * b;
    }
    quarter which_quarter () const {
        if (x > 0 && y > 0) return quarter::first;
        if (x < 0 && y > 0) return quarter::second;
        if (x < 0 && y < 0) return quarter::third;
        if (x > 0 && y < 0) return quarter::fourth;
        return quarter::none; //linia
    }
    void print() {
        std::cout << x << "\t" << y << "\t" << r << "\t" << g << "\t" << b << "\t" << name << std::endl; 
    }
};

int main() {
    std::list<point> points = {
        point ( 6, 2, 65,  45, 217, "abf"),
        point ( 1, 2, 0, 0, 22, "ad"),
        point ( 2, -7, 136, 161, 231, "abc"),
        point ( 56, -6, 231,  41, 172, "fgh"),
        point (-48,  5, 196,  34,  15, "erfv"),
        point (-100,  7, 17,  27,   1, "pfee"),
        point (-33,  3, 16,   114,  61, "jythr"),
        point (-44, -3, 12,  100, 102, "nfer"),
        point (0, -13, 174, 21, 107, "ogrfe"),
        point (-82,  3, 11, 23, 177, "fffa"),
        point (-83,  33, 145,  12, 184, "1fef3"),
        point ( 53,  23, 13,  55, 201, "grf"),
        point ( 72, -3, 79, 196, 100, "ppdfesdcpa"),
        point ( -63, 6, 112, 201,  10, "sifrdeiosae"),
        point ( 92,  3, 177,  65,   1, "a"),
        point (-33,  0, 17,   45,  11, "dasoeese"),
        point (133,  1, 127,  57,  23, "nn")
    };
    std::cout<<"Points:\n";
    for(auto it: points)
		it.print();

    points.remove_if([](const point &a) -> bool { return a.get_name().size() > 5; });
	std::cout<<"Points with name longer than 5 removed:\n";
	for(auto it: points)
		it.print();

    int first =  std::count_if(points.begin(), points.end(), [](const point &a) -> bool { return a.get_x() > 0 && a.get_y() > 0; });
    int second = std::count_if(points.begin(), points.end(), [](const point &a) -> bool { return a.get_x() < 0 && a.get_y() > 0; }); 
    int third =  std::count_if(points.begin(), points.end(), [](const point &a) -> bool { return a.get_x() < 0 && a.get_y() < 0; });
    int fourth = std::count_if(points.begin(), points.end(), [](const point &a) -> bool { return a.get_x() > 0 && a.get_y() < 0; });
    int none =   std::count_if(points.begin(), points.end(), [](const point &a) -> bool { return a.get_x()== 0 || a.get_y()== 0; });
    std::cout << "Points in first quarter:  " << first  << std::endl;
    std::cout << "Points in second quarter: " << second << std::endl;
    std::cout << "Points in third quarter:  " << third  << std::endl;
    std::cout << "Points in fourth quarter: " << fourth << std::endl;
    std::cout << "Points lying on line:     " << none   << std::endl << std::endl;


    points.sort([](const point& a, const point& b) {
        return a.brightness() < b.brightness(); 
    });
    std::cout<<"Sorted by brightness:\n";
    for(auto it: points)
		it.print();
	
    std::list<point> dark_points;
    for(auto it: points)
		if(it.brightness() < 64) 
			dark_points.push_back(it);
   std::cout<<"Dark points:\n";
    for(auto it: dark_points)
		it.print();
	
}
