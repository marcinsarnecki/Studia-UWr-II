#include <bits/stdc++.h>
#include <random>

class matrix{ //macierz o rozmiarze n x n
	private:
		std::vector<std::vector<double>> m;
		static double randomNumber()
		{
			static std::mt19937 generator{std::random_device()()};
			return std::uniform_real_distribution<double>(0.5, 2.0)(generator);
		}
	public:
	int N;
		matrix(int n) {
			N = n;
			m.resize(n);
			for(int i = 0; i < n; i++)
				m[i].resize(n, 0.0);
		}
		matrix() {
			N = 0;
		};
		matrix(matrix&& m2) {
			N = m2.N;
			m = std::move(m2.m);
		}
		matrix& operator=(matrix&& m2) {
			if(this == &m2)
				return *this;
			N = m2.N;
			m = std::move(m2.m);
			return *this;
		}
		void random_fill() {
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					m[i][j] = randomNumber();
		}
		void print() {
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++)
					std::cout<<m[i][j]<<" ";
				std::cout<<"\n";
			}
		}
		void square() {
			matrix ans(N);
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++) {
					double sum = 0;
					for(int k = 0; k < N; k++)
						sum += m[i][k] * m[k][j];
					ans.m[i][j] = sum;
				}
			(*this) = std::move(ans);
		}
	
	};

void measureTime(matrix& m, int iterations)
{
    using namespace std::chrono;
    auto startTime = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++)
        m.square();
    auto endTime = high_resolution_clock::now();
    auto time = duration_cast<duration<double>>( (endTime - startTime) / iterations );
    std::cout<<std::fixed<<std::setprecision(4);
    std::cout << m.N << "x" << m.N << " multiplication time: " << time.count() << "s\n";
}


int main() {
	//~ matrix m(5);
	//~ m.random_fill();
	//~ m.print();
	//~ m.square();
	//~ m.print();
	
	matrix m10(10);
    matrix m100(100);
    matrix m1000(1000);

    measureTime(m10, 1000);
    measureTime(m100, 100);
    measureTime(m1000, 1);
	return 0;
}
