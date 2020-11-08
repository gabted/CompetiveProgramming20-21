#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Execution time on G4G: 1325ms
	
	Correctness: Algotirhm presented in class
		
	Time complexity: O(nlogn)
			
	Space complexity: O(n)
		
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

struct Segment{
	int start;
	int end;
	int order;
	uint64_t nested_segments;
};

bool compareSegments(Segment a, Segment b){
	return a.start < b.start;
}

bool originalOrder(Segment a, Segment b){
	return a.order < b.order;
}

int main() {

    std::vector<Segment> vec;
    std::vector<int> ends;
	int n {};
	//collect data
	std::cin >> n;
	vec.reserve(n);
	ends.reserve(n);
 	int l {}, r{};
	for (int i {}; i < n; ++i) {
		std::cin >> l;	
		std::cin >> r;
		vec.push_back({l, r, i, 0});
		ends.push_back(r);
	}
	
	//elaborate data
	sort(ends.begin(), ends.end());
	sort(vec.begin(), vec.end(), compareSegments);
	vector<uint64_t> BIT(n+1);
	for(auto it = vec.begin(); it<vec.end(); ++it){
		int end = it->end;
		end = lower_bound(ends.begin(), ends.end(), end) - ends.begin();
		fenwick_update(BIT, end+1, 1);
		it->end = end;
	}	
	
	for(auto it = vec.begin(); it<vec.end(); ++it){
		it->nested_segments = fenwick_sum(BIT, it->end);
		fenwick_update(BIT, (it->end)+1, -1);
	}
	
	sort(vec.begin(), vec.end(), originalOrder);
	for(Segment segment : vec)
		cout<<segment.nested_segments<<endl;
	
	
	

    return 0;
}