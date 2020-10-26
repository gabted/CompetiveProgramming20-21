#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
	Execution time on G4G: 
	
	Correctness:
		
	Time complexity:
			
	Space complexity:
		
*/

int fenwick_sum(std::vector<int> B, int i){
	int sum {};
	while(i != 0){
		sum += B[i];
		i -= i & -i;
	}
	return sum;
}

void fenwick_update(std::vector<int> &B, int i, int v){
	while(i < B.size()){
		B[i] += v;
		i += i & -i;
	}
}


int main() {
	int n {};
	int x {};
	std::vector<int> vec;
    std::unordered_map<int, int> map;
	
	//collect data
    cin >> n;
    vec.reserve(n);
	map.reserve(n);
	for (int i {}; i < n; ++i) {
		scanf("%d", &x);
		vec.push_back(x);
	}
	
	//create prefix counter array
	//P[i] = f(1, i, a_i)
	int max {};
	std::vector<int> P;
	for(auto it = vec.begin(); it <vec.end(); ++it){
		int value = ++map[*it];
		P.push_back(value);
		max = (max < value)?value:max;
	}
	map.clear();
	
	//create suffix counter array
	//S[j] = f(j, n, a_j)
	std::deque<int> S(n);
	for(auto it = vec.rbegin(); it <vec.rend(); ++it)
		S.push_front(++map[*it]);

	//scans P backward, for each possible i
	//counts the possible js.
	std::vector<int> BIT(max);
	int result {};
	for(int  i=n-1; i>=0; --i){
		result += fenwick_sum(BIT, P[i]-1);
		fenwick_update(BIT, S[i], 1);
	}
	cout<<result;
	
	
	
    return 0;
}