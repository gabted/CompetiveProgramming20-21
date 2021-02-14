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
		
*/

//global variables
int buckSize;
std::vector<int> vec;
std::unordered_map<int, int64_t> counters;
int64_t partial_result {};

//functions and structs to sort the queries
struct query{
	int l;
	int r;
	int64_t result;
	int index;
};

bool compare(query &a, query &b){
	int bucket_a = a.l / buckSize;
	int bucket_b = a.l / buckSize;
	if(bucket_a == bucket_b)
		return a.r < b.r;
	else
		return bucket_a < bucket_b;

	return true;
}

bool reorder(query &a, query &b){
	return a.index < b.index;
}


//############functiosn of Mo algorithm
void add(int p){
	int value = vec[p];
	int64_t occurencies = counters[value];
	partial_result -= value*occurencies*occurencies;
	++counters[value];
	++occurencies;
	partial_result += value*occurencies*occurencies;
}

void remove(int p){
	int value = vec[p];
	int64_t occurencies = counters[value];
	partial_result -= value*occurencies*occurencies;
	--counters[value];
	--occurencies;
	partial_result += value*occurencies*occurencies;
}

int main() {
	int n {};
	int t {};
	scanf("%d%d", &n, &t);
	//std::cin >> n;
	//std::cin >> t;
	
	//collect data
	vec.reserve(n+1);
	vec.push_back(0);
	for (int i {}; i < n; ++i) {
		int x {};
		scanf("%d", &x);
		//std::cin >> x;
		vec.push_back(x);
	}
	
	
	//collect queries
    std::vector<query> queries;
	queries.reserve(t);
	for (int i {}; i < t; ++i) {
		int x {};
		int y {};
		scanf("%d%d", &x, &y);
		//std::cin >> x;
		//std::cin >> y;
		queries.push_back({x, y, 0, i});
	}
	//sorting queries
	buckSize = sqrt(n);
	sort(queries.begin(), queries.end(), compare);	
	
	
	//execute queries
	int curr_l = 0;
	int curr_r = 0;
	//counters = std::unordered_map<int, int64_t>();
	//counters.max_load_factor(0.25);
	counters.rehash(n+1);
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