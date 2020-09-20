#include <iostream>
#include <vector>
#include <algorithm>

/*
	Execution time on G4G: 0.39
	
	
	Correctness:
		For each i in [0, vec.size()), the quantity of trappable water is bounded by the minimum of the highest 
		blocks in the prefix and in the suffix of i. Obviously from this minumum it has to be subtracted the 
		"space occupyed by the i-th block", i.e. vec[i].
	
	Time complexity: O(n)
		The algorithm scans the vector three times: two for computing the prefix-maxima and suffix-maxima,
		ad one for computing the actual water level.
	
	Space complexity: O(n)
		Beside allocating a vector to store the input data, the algorithm allocates two more vector, 
		to store the maxima. This could be improbed by allocating only one additional vector,  filling it
		with prefix-maxima, and then storing min(prefix-max, suffix-max).
*/

void print_trapped_water(std::vector<int> const& vec){
	int max {};
	
	//compute all the prefix maxima
	std::vector<int> prefix_max;
	prefix_max.reserve(vec.size());
	max = -1;
	for(int i = 0; i<vec.size(); ++i){
		if(max < vec[i])
			max = vec[i];
		prefix_max[i] = max;
	}
	
	//compute all the suffix maxima
	std::vector<int> suffix_max;
	suffix_max.reserve(vec.size());
	max = -1;
	for(int i = vec.size()-1; i >= 0; --i){
		if(max < vec[i])
			max = vec[i];
		suffix_max[i] = max;
	}
	
	int total_water {};
	//select the min beween prefix and suffix maximum
	for(int i = 0; i<vec.size(); ++i){
		total_water += std::min(prefix_max[i], suffix_max[i]) - vec[i];
	}
	
	std::cout << total_water <<std::endl;
}

int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {};
        std::cin >> n;
        vec.reserve(n);
        for (int i {}; i < n; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		print_trapped_water(vec);
		
		
		//clear data
        vec.clear();
    }

    return 0;
}