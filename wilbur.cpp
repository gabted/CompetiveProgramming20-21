#include <iostream>
#include <vector>
using namespace std;

/*
	Execution time on codeforces: 405 
	
	Correctness:
		we follow a greedy approach that sets all the elements of the array in order,
		thanks to the osservation that, if an optimal solutions executes operations on the 
		j-suffix before operations on the i-suffix, with i<j, doing these operations in an ordered
		fashion, i.e. setting i before j, will produce the same optimal result.
		
	Time complexity: O(n)
			
	Space complexity: O(1)
		
*/

int main() {
	
	int n {};
	std::cin >> n;
	
	int64_t prev = 0;
	int64_t curr = 0;
	int64_t tot = 0;
	for (int i {}; i < n; ++i) {
		cin >> curr;
		tot += abs(curr-prev);
		prev = curr;
	}
	cout << tot;
	
    return 0;
}