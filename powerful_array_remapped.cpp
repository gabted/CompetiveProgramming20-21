#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>

using namespace std;

/*
	Execution time on G4G: exeeded on test 6
	
	Correctness: 
		this is a simple application of Mo algorithm
		
	Time complexity:
		amortized cost is O((n+t)sqrt(n))
			
	Space complexity: O(n)
		used for remapping. Using a proper hashmap, it could be O(k),
		where k is the number of distinct input element.
		
*/

//global variables
int buckSize;
std::vector<int> vec;
std::vector<int> remapped;
std::vector<int64_t> counters;
int64_t partial_result {};

//utility remap function
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

//functions and structs to sort the queries
struct query{
	int l;
	int r;
	int result;
	int index;
};

bool compare(query a, query b){
	int bucket_a = a.l / buckSize;
	int bucket_b = a.l / buckSize;
	if(bucket_a == bucket_b)
		return a.r < b.r;
	else
		return bucket_a < bucket_b;

	return true;
}

bool reorder(query a, query b){
	return a.index < b.index;
}


//############functiosn of Mo algorithm
void add(int p){
	partial_result -= vec[p]*counters[remapped[p]]*counters[remapped[p]];
	counters[remapped[p]]++;	
	partial_result += vec[p]*counters[remapped[p]]*counters[remapped[p]];
}

void remove(int p){
	partial_result -= vec[p]*counters[remapped[p]]*counters[remapped[p]];
	counters[remapped[p]]--;	
	partial_result += vec[p]*counters[remapped[p]]*counters[remapped[p]];
}

int main() {
	int n {};
	int t {};
	std::cin >> n;
	std::cin >> t;
	
	//collect data
	vec.reserve(n+1);
	vec.push_back(0);
	for (int i {}; i < n; ++i) {
		int x {};
		std::cin >> x;
		vec.push_back(x);
	}
	//remapping data
	remapped = vector<int>(vec.size());
	copy(vec.begin(), vec.end(), remapped.begin());
	remap<int>(remapped);
	
	
	//collect queries
    std::vector<query> queries;
	queries.reserve(t);
	for (int i {}; i < t; ++i) {
		int x {};
		int y {};
		std::cin >> x;
		std::cin >> y;
		queries.push_back({x, y, 0, i});
	}
	//sorting queries
	buckSize = sqrt(n);
	sort(queries.begin(), queries.end(), compare);	
	
	
	//execute queries
	int curr_l = 0;
	int curr_r = 0;
	counters = vector<int64_t>(n+1);
	for(int k {}; k<t; k++){
		query q = queries[k];
		while(curr_l < q.l){
			remove(curr_l);
			++curr_l;
		}
		while(curr_l > q.l){
			--curr_l;
			add(curr_l);
		}
		while(curr_r < q.r){
			++curr_r;
			add(curr_r);
		}
		while(curr_r > q.r){
			remove(curr_r);
			--curr_r;
		}
		
		queries[k].result = partial_result;		
	}
	
	//sort and print
	sort(queries.begin(), queries.end(), reorder);
	for(auto q : queries)
		cout<<q.result<<endl;


    return 0;
}