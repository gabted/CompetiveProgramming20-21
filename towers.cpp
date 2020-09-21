#include <iostream>
#include <unordered_map>

/*
	Execution time on CodeForces: 92 ms 
	
	Complexity: O(n)
		For this problem, there were two ways:
			-minimize time complexity, and use a hashmap for counting occurencies in average linear time
			-minimize space complexity, and sort the input in costant space
		I preferred the first approach, which has a linear time complexity, but has to allocate a hashmap 
		to count occurencies. In the worst case, in n input there will be n different numbers, and so the space
		complexity is linear. (In that case, the actual space occupied will be great than n, and it will dipend on
		map.max_load_factor())
*/
int main() {

    std::unordered_map<int, int> map;
	int n {};
	std::cin >> n;
	
	int max_occ {};
	for (int i {}; i < n; ++i) {
		int x {};
		std::cin >> x;
		int current_occ = ++map[x];
		if (max_occ < current_occ)
			max_occ = current_occ;
	}
	std::cout <<max_occ <<" "<<map.size();


    return 0;
}