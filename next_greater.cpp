#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/*
	Execution time on G4G: 0.8
	
	Correctness:
		The main idea of this algorithm is to visit the data vector backwards, storing longer 
		and longer suffixes in a separate data structure S. If S is ordered and contains all elementst
		A[i+1]..A[n], to find the next greater element of i it is sufficient to scan S and select the 
		first element greater than i.
		In order to find the optimal data structure for S, it's relevant the following propriety:
			For all i, if Exixst j<i s.t. A[i] > A[j], A[i] will never be the next greater element for any
			z<=j.
		In a intuitive sense, every search for a next greater element starting before j, will stop at most at A[j], 
		and never reach A[i]. This mean that A[i] can effectively be discarded from S, as soon as we find a j-th
		element greater then A[i].
		S is here implemented as a stack, with the following insertion algorithm: when adding an element x, 
		all the y1, y2, y3.. element smaller then x will be popped out of the stack. By induction on the lenght of the 
		stack, we can prove that the stack will always be ordered, and after having inserted the element x, its next greater element will
		be next element in the stack. Thanks to the previous propriety of the problem, discarding all the smaller elements has no effect
		on the solution.
		
	Time complexity: O(n)  ?
		In principle, scanning the n elements in the stack for n time would require O(n^2) moves. This upper bound can be
		refined with amortized analysis. In a bad case scenario, like the array [10, 1, 2, 3, 4, 5, 6, 7, 8, 9], the last insetion will require
		n-1 pops of the stack. But it is also true that in order to create such a log stuck, the previous element are all ordered, and each of 
		these required a O(1) insertion. Besides, After the insertion of 10, the stack will be drastically reduced in size, and the following insetion
		will happen quicker. In conclusion the insertion will happen in amortized costant time, and so the algorithm is linear.
	
	Space complexity: O(n) in the worst case scenario, smaller in the average case
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