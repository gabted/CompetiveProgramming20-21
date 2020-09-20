#include <iostream>
#include <vector>
#include <numeric>


/*
	This code was explained in the first lesson
	
	execution time on G4G: 0.54
*/

void find_missing(std::vector<int> const& vec){
	int n = vec.size()+1;
	int tot = n*(n+1)/2;
	int sum = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << tot-sum << std::endl;
}

int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {};
        std::cin >> n;
        vec.reserve(n-1);
        for (int i {}; i < n-1; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		find_missing(vec);
		
		//clear data
        vec.clear();
    }

    return 0;
}