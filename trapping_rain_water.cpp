#include <iostream>
#include <vector>

void print_trapped_water(std::vector<int> const& vec){
	
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