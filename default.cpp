#include <iostream>
#include <vector>

/*
	Execution time on G4G: 
	
	Correctness:
		
	Time complexity:
			
	Space complexity:
		
*/

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
		
		
		//clear data
        vec.clear();
    }

    return 0;
}