#include <iostream>
#include <vector>
#include <set>	

/*
	Execution time on G4G: 1.9
	
	Time complexity: O(n*log(k))
		The algorithm represents the current window with a multiset (with logarithmic insertion, 
		extraction and query time). Calculating the maximum for n-k+1 windows, this algorithm executes in O(n*log(k)).
	
	Space complexity: O(k)
		Due to the balanced BST implementation of the multiset
*/

void print_max_of_subarray(std::vector<int> const& vec, int k){
	//build the set of the first k elements
	std::multiset<int> set;
	for(int i{}; i<k; ++i)
		set.emplace(vec[i]);
	std::cout << *set.rbegin() << " ";
	
	//scan the array, printing the max of each set
	for(int i {k}; i<vec.size(); ++i){
		set.erase(set.find(vec[i-k]));		//erases the element just exited from the window
		set.emplace(vec[i]);				//adds the element just entered the window
		std::cout << *set.rbegin() << " ";	//print the new maximum
	}
	
	std::cout << std::endl;
}

int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int t {}; t < num_test_cases; ++t) {
		//collect data
		int n {}, k {};
        std::cin >> n;
        std::cin >> k;
        vec.reserve(n);
        for (int i {}; i < n; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		print_max_of_subarray(vec, k);
		
		//clear data
        vec.clear();
    }

    return 0;
}