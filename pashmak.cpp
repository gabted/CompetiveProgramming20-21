#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
	Execution time on Codeforces: 436 
	
	Correctness: 
		To compute #{(i, j) with i<j | f(1, i, vec[i]) > f(j, n, vec[j])},
		we should count, for each i, the number of js greater then i that respect the condition.
		Let's call g(j) = f(j, n, vec[j]). Given an array P for wich P[i] = f(1, i, vec[i]),
		we can count, for each i, #{j with i<j| g(j)<P[i]} using a fenwick tree, as explained in the code.
		
	Time complexity: O(n)
		The algorithm remaps the array in O(nlogn) steps, then scans it one time
		foreward, O(n), and one time backword, executing two fenwick operation at
		each step, O(nlogn).
	
			
	Space complexity: O(n)
		O(n) to execute remappint, + O(d) to store the BIT, where
		d is the greatest number of occurencies of an element, so O(n+d) = O(n)
		
*/

uint64_t fenwick_sum(std::vector<uint64_t> &B, int i){
	uint64_t sum {};
	while(i != 0){
		sum += B[i];
		i -= i & -i;
	}
	return sum;
}

void fenwick_update(std::vector<uint64_t> &B, int i, int v){
	while(i < B.size()){
		B[i] += v;
		i += i & -i;
	}
}

template<typename T> 
void remap(vector<T>& a) {
  vector<T> tmp(a.size());
  copy(a.begin(), a.end(), tmp.begin());
  sort(tmp.begin(), tmp.end());
  size_t sz = distance(tmp.begin(), unique(tmp.begin(), tmp.end()));
  tmp.resize(sz);
  
  for(auto &x : a)
    x = distance(tmp.begin(), lower_bound(tmp.begin(), tmp.end(), x));
}

int main() {
	int n {};
	int x {};
	std::vector<int> vec;	
	
	//collect data
    cin >> n;
    vec.reserve(n);
	std::vector<int> occurencies(n);
	for (int i {}; i < n; ++i) {
		scanf("%d", &x);
		vec.push_back(x);
	}
	remap<int>(vec);
	
	//create prefix counter array
	//P[i] = f(1, i, a_i)
	std::vector<uint64_t> P;
	uint64_t max{};
	uint64_t curr_occ {};
	for(auto it = vec.begin(); it <vec.end(); ++it){
		curr_occ = ++occurencies.at(*it);
		P.push_back(curr_occ);
		max = (max < curr_occ)?curr_occ:max;
	}
	fill(occurencies.begin(), occurencies.end(), 0); 

	//scans P backward, for each possible i counts the possible js.
	//lets call g(j) = f(j, n, vec[j]). We need to know x, the number of js (greater then i) 
	//for which g(j) < P[i]. This x is equal to Sum from t=0 to P[i]-1 of k_t, where 
	//k_t = #{j | g(j)=t}. These values k_t can be stored in a fenwick tree,
	//inscreasing BIT(k_t) every time we found a j with g(j) = t.
	//In order to consider only the valid values (i.e. the values g(j) for j > i), 
	//this fenwick tree can be constructed
	//alongside the backword scannign of the array.
	std::vector<uint64_t> BIT(max);
	uint64_t result {};
	for(int  i=n-1; i>=0; --i){
		result += fenwick_sum(BIT, P[i]-1);
		fenwick_update(BIT, ++occurencies.at(vec[i]), 1);
	}
	cout<<result;
	
	
	
    return 0;
}