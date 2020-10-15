#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
/*
	Execution time on G4G: 0.16s
	
	Time complexity: O(n+u+q)
		The updates are stored with u costant time accesses, then are applied 
		with a single O(n) scan. The queries are resolved with q costant time accesses.
			
	Space complexity: O(n)
		it uses only the input vector, overwriting it with the prefix sums.
		
*/

int main() {

    int num_test_cases {};
    cin >> num_test_cases;

    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {}, u {}, q {};
        cin >> n;
        cin >> u;
        
		//collect updates
		//+1 to store the eventual right delimiters
		std::vector<int64_t> vec(n+1);	
        int l {}, r{}, val{};
        for (int i {}; i < u; ++i) {
            scanf("%d%d%d", &l, &r, &val);
            vec.at(l) += val;
            vec.at(r+1) += -val;
        }
		vec.pop_back();
		
		//apply updates
		std::partial_sum(vec.begin(), vec.end(), vec.begin());
        
		//collect queries;
		cin >> q;
		int query {};
		for(int i {}; i<q; ++i){
			scanf("%d", &query);
			printf("%d\n", vec.at(query));
		}
		
		//clear data
        vec.clear();
    }

    return 0;
}