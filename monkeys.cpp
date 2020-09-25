#include <iostream>
#include <vector>

/*
	Execution time on Online Judge: 0.12 sec 
	
	Correctness:
		This algorithm emplys a greedy strategy: at each steps it chooses the optimal solution
		statisfying the costraints met so far, upgrading that solution (keeping it optimal) 
		when encountering stricter costraints.
		The input data is stored in a vector, preceded by an element 0. This is done because the
		algorithm is intrested in "steps" on the ladder, i.e. in the difference between one number
		and the previous. So starting to climbing the ladder can be seen as doing a jump from height 0
		to height x, where x it's the first number in the input of the test case.
		The algorithm scans the vector backward, and it can be proved by induction (on the lenght of the already
		visited suffix) that the correct and optimal solution "k" is stored inside required_force.
		The 0-lenght case is trivial, no force is needed to climb.
		If k is the (optimal) solution for the previous n elements, there are three different cases to be mmade:
			if the current "step" (on the ladder) is lesser then k, then k is a valid solution, and is optimal for inductive ipothesis.
			if the current "step" is equal to k, then k+1 is the optimal correct solution, cause k would not be enough
			if the current "step" is bigger then k, then the step itsef is the optimal solution.
		
	Time complexity: O(n)
		the algorithm scans backward the input just one time.
			
	Space complexity: O(1)
		
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