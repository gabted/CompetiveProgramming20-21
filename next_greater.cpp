#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/*
	Execution time on G4G: 0.8
	
	Correctness:
		The main idea of this algoorithm is to visit the data vector backwards, storing longer 
		and longer suffixes in a separate data structure S. If S is ordered and contains all elementst
		A[i+1]..A[n], to find the next greater element of i it is sufficient to scan S and select the 
		first element greater then i.
		In order to find the optimal data structure for S, it's relevant the following propriety:
			For all i, if Exixst j<i s.t. A[i] > A[j], A[i] will never be the next greater element for all
			z<=j.
		In a intuitive sense, every search for a next greater element starting before j, will stop at most at A[j], 
		and never reach A[i]. This mean that A[i} can effectively be discarded from S, as soon as we find a j-th
		element greater then A[i].
		Knowing that, it's 
	Time complexity: O(n)
			
	Space complexity: O(n)
		
*/

void print_next_greater(std::vector<long> const& vec){
	std::stack<long> stack;
	std::vector<long> output;
	output.reserve(vec.size()); 
	
	//the last element has no following element
	stack.emplace(vec.back());
	output.push_back(-1);
	
	for(auto i = vec.rbegin()+1; i < vec.rend(); ++i){
		while(!stack.empty() && stack.top() <= *i)
			stack.pop();
		if(stack.empty())
			output.push_back(-1);
		else
			output.push_back(stack.top());
		stack.emplace(*i);
	}
	
	
	auto print = [](long n){std::cout << n << " ";};
	std::for_each(output.rbegin(), output.rend(), print);
	std::cout << std::endl;
}

int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<long> vec;
    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {};
        std::cin >> n;
        vec.reserve(n);
        for (int i {}; i < n; ++i) {
            long x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		print_next_greater(vec);
		
		//clear data
        vec.clear();
    }

    return 0;
}