#include<bits/stdc++.h>

int main(int argc, char** argv) {
    if (argc < 2) 
        return 1;
    std::string s(argv[1]);
    std::sort(s.begin(), s.end());
    do {
        std::cout<<s<<"\n";
    }while(std::next_permutation(s.begin(), s.end()));
}
