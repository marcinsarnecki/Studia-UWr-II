#include <bits/stdc++.h>

int main(int argc, char** argv) {
    if (argc < 2) 
        return 1;
    std::fstream file(argv[1], std::ios::in);
    std::string content;
    getline(file, content, (char)26);//eof ma kod ascii 26
    int all = 0;
    std::vector<int> l(26, 0);
    for (auto it: content) {
        all++;
        if(it >= 65 && it <= 90)
			l[it-65]++;
		if(it >= 97 && it <= 122)
			l[it-97]++;
    }
    std::cout<<std::fixed<<std::setprecision(2);
    for (int i = 0; i < 26; i++) 
        std::cout <<(char)(i + 97)<<": " << l[i]<< "\t" << (double)l[i] / all * 100 << "%" << std::endl;
}
