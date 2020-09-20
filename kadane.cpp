#include <iostream>
#include <vector>

/*
	This code was explained in the first lesson
	
	execution time on G4G: 0.29
*/

void print_max_subarray(std::vector<int> const& vec){
	int sum = vec.front(); // thus skip first element
    int max_sum = sum;

    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        if (sum > 0) {
            sum += *it;
        } else {
            sum = *it;
        }

        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    std::cout << max_sum << std::endl;
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
		print_max_subarray(vec);
		
		//clear data
        vec.clear();
    }

    return 0;
}