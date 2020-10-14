#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

/*
	Execution time on G4G: 1964ms
	
	Correctness: the Algorithm was presented during the lesson
		
	Time complexity: O(nlogn) + O(mlogm)
		After ordering the (extremes of the) queries, the P vector si costructed in linear time,
		then P and the inpu array are sorted.
			
	Space complexity: O(m), for the queries extremes
		
*/

bool compare(int a, int b){
	return (abs(a)<abs(b));
}

void searchMaxSumPermutation(std::vector<int> &vec, std::vector<int> &queries){
	//order queries extremes
	std::sort(queries.begin(), queries.end(), compare);
	
	//builds P, containing the number of queries including each element
	std::vector<int> P;
	P.reserve(vec.size());
	int counter {};	//while i proceeds, counter represents 
					//number of queries which include i
	//i advances over vec, j over queries
	for(int i {}, j{}; i<vec.size(); ++i){
		while(i == abs(queries[j]) && j<queries.size()){
			//if i find an opening extreme, increase counter,
			//i.e. the number of intersecting segment 
			if(queries[j]>=0)
				++counter;
			//if i found a closing extreme, decrease counter
			//a segment (x, y) is stored as (x, -(y+1)), so if
			//y is a closing extreme, the last index in the segment was y-1
			else
				--counter;
			++j;
		}
		P.push_back(counter);
	}
	
	std::sort(P.begin(), P.end());
	std::sort(vec.begin(), vec.end());
	int64_t factor1 {};
	int64_t factor2 {};
	int64_t totalsum {};
	for(int i {}; i<vec.size(); ++i){
		factor1 = vec[i];
		factor2 = P[i];
		totalsum += factor1*factor2;
	}
	
	std::cout<<totalsum;	
}

int main() {

	//collect data
	int n {};
	std::cin >> n;
	int q {};
	std::cin >> q;		
	//collect numbers
    std::vector<int> vec;
	vec.reserve(n);
	for (int i {}; i < n; ++i) {
		int x {};
		std::cin >> x;
		vec.push_back(x);
	}
	
	//collect queries
	std::vector<int> queries;
	queries.reserve(2*q);
	int start {}, end {};
	for (int i {}; i < q; ++i) {
		std::cin >> start;
		std::cin >> end;
		//query (x, y) is stored as (x, -(y+1))
		//y points to the value after the end of the segment
		//positive elements are starting points of queries,
		//negative elements are ending points
		queries.push_back(start-1);
		queries.push_back(-end);	
	}
	
	//elaborate data
	searchMaxSumPermutation(vec, queries);
	
	//clear data
	vec.clear();

    return 0;
}