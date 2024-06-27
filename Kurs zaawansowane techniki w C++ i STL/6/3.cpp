#include <bits/stdc++.h>

int main() {
    std::vector elements({2, 3, 5, 4, 2, 4, 5, 7, 4, 8, 4, 6, 3, 2, 5, 4, 6, 3, 2, 1, 1, 1, 2, 9});
    std::map<int,int> m;
    for(auto it: elements)
		m[it]++;
	int ans = 0;
	for(auto it: m)
		ans = std::max(ans, it.second);
	for(auto it: m)
		if(it.second == ans)
			std::cout<<it.first<<" "<<it.second<<"\n";
}
