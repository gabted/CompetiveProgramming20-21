#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
	Execution time on G4G: 
	
	Correctness:
		
	Time complexity:
			
	Space complexity:
		
*/

struct query{
	int l;
	int r;
};

//global variables
int n {};
int buckSize;
std::vector<int> vec;


bool compare(query a, query b){
	int bucket_a = a.l / buckSize;
	int bucket_b = a.l / buckSize;
	if(bucket_a == bucket_b)
		return a.r < b.r;
	else
		return bucket_a < bucket_b;

	return true;
}

void add(int p){
	
}

void remove(int p){
	
}

int main() {
	int t {};
	std::cin >> n;
	std::cin >> t;
	
	//collect data
	vec.reserve(n);
	for (int i {}; i < n; ++i) {
		int x {};
		std::cin >> x;
		vec.push_back(x);
	}
	
	
    std::vector<query> queries;
	queries.reserve(t);
	for (int i {}; i < t; ++i) {
		int x {};
		int y {};
		std::cin >> x;
		std::cin >> y;
		queries.push_back({x, y});
	}

	//elaborate data
	buckSize = sqrt(n);
	sort(queries.begin(), queries.end(), compare);
	
	int curr_l {};
	int curr_r {};
	for(auto q : queries){
		while(curr_l < q.l){
			remove(curr_l);
			++curr_l;
		}
		while(curr_l > q.l){
			add(curr_l);
			--curr_l;
		}
		while(curr_r < q.r){
			add(curr_r);
			++curr_r;
		}
		while(curr_r > q.r){
			remove(curr_r);
			--curr_r;
		}
	}


    return 0;
}