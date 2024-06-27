#include <iostream>
#include <set>

using zbior = std::set<std::string>;

int main() {
    zbior stl {"queue", "map", "set", "vector", "list", "unordered_map", "priority_queue", "unordered_set", "stack"};
    for(auto it: stl)
        std::cout<<it<<"\n";
    return 0;
}