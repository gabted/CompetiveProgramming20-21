#include <iostream>
#include <vector>

/*
	Execution time on G4G: 
	
	Correctness:
		
	Time complexity:
			
	Space complexity:
		
*/

int calculate_min_force(std::vector<int> const& vec){
	int required_force = {};
	
	for(int i = vec.size()-1; i>0; --i){
		int step = vec[i] - vec[i-1];
		//std::cout<<step<<" ";
		if(step > required_force)
			required_force = step;
		else if(step == required_force)
			++required_force;
	}
		
	return required_force;
}

int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {};
        std::cin >> n;
        vec.reserve(n+1);
		vec.push_back(0);
        for (int i {}; i < n; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		int out = calculate_min_force(vec);
		std::cout << "Case "<<k+1<<": "<<out<<std::endl;
		
		//clear data
        vec.clear();
    }

    return 0;
}