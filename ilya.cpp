#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/*
	Execution time on codeForces: 1120ms
	
	Correctness:
		from the string we build a vector A of 0s and 1s, where
		A[i] = 1 iff A[i] == A[i+1], with i in [0, n-1]
		The answer to a query (l, r) is the sum of the values in 
		range [l, r-1]. This sum can be solved i nconstant time if we 
		precompute the prefix sum, and execute the range sum in the usual
		"sum(i, j) = P[j] - P[i-1]" way.
		
	Time complexity:O(n+m)
			
	Space complexity: O(n)
		
*/

int main() {



	//collect data
	string s;
	getline(cin, s);
	int n = s.length();
	vector<int> vec;
	vec.reserve(n);
	vec.push_back(0);	//the first element, with index 0, is a dummy value
	//i store only values for elements s[0, n-2]
	//because the value for s[n-1] is usless and can be discarded
	for (int i {}; i < n-1; ++i)	
		vec.push_back(s[i]==s[i+1]);

	//elaborate data
	std::partial_sum(vec.begin(), vec.end(), vec.begin());
	int m {};
	int l {};
	int r {};
	cin >> m;
	for(int i {}; i<m; ++i){
		cin >> l;
		cin >> r;
		cout << vec[r-1] - vec[l-1] << endl;
	}
	
		
		

    return 0;
}