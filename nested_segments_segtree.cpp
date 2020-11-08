#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/*
	Execution time on G4G: 1388ms
	
	Correctness: Algotirhm presented in class
		
	Time complexity: O(nlogn)
			
	Space complexity: O(n)
		
*/

int left_child(int index){
	return 2*index+1;
}
int right_child(int index){
	return 2*index+2;
}
	
	
//gets the sum of the elements in [left, right] inside 
//the subtree rooted in root, which spans over [start, end]
uint64_t sum_rec(vector<uint64_t> &tree, int root, int start, int end, int left, int right){
	if(left <= start && end <= right)		//if [start, end] is inside de query
		return tree[root];
	else if(end < left || right < start)	//if [start, end] is outside the query
		return 0;
	else{		//if [start end] is partialli inside the query		
		int mid = (start + end)/2;
		return sum_rec(tree, left_child(root), start, mid, left, right) 
			+ sum_rec(tree, right_child(root), mid+1, end, left, right);
	}
}


uint64_t sum(vector<uint64_t> &tree, int n, int left, int right){
	return sum_rec(tree, 0, 0, n-1, left, right);
}

//walks the tree and adds value to index and all its ancestors
void update_rec(vector<uint64_t> &tree, int root, int start, int end, int index, int value){
	if(start == end){
		tree[root] += value;
	}
	else{
	tree[root] += value;
	int mid = (start + end)/2;
	if(index <= mid)
		update_rec(tree, left_child(root), start, mid, index, value);
	else
		update_rec(tree, right_child(root), mid+1, end, index, value);
	}
}


//adds value to th element index-th value (in the original array of n elements)
void update(vector<uint64_t> &tree, int n, int index, int value){
	update_rec(tree, 0, 0, n-1, index, value);
}

//fills the subtree rooted in "root", representing
//the range [start, end]	
void build_rec(vector<uint64_t> &tree, int root,int start,int end){
	if(start == end){
		cin >> tree[root];
	}
	else{	
		int mid = (start + end)/2;
		build_rec(tree, left_child(root), start, mid);
		build_rec(tree, right_child(root), mid+1, end);
		tree[root] = 
			tree[left_child(root)] + tree[right_child(root)];
	}
}

vector<uint64_t>& build_segment_tree(int n){
	int h = (int) ceil(log2(n));
	int size = 2*(int)pow(2, h) - 1;
	static vector<uint64_t> tree(size);
	//build_rec(tree, 0, 0, n-1);
	return tree;
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
	vector<uint64_t> segtree = build_segment_tree(n);
	for(auto it = vec.begin(); it<vec.end(); ++it){
		int end = it->end;
		end = lower_bound(ends.begin(), ends.end(), end) - ends.begin();
		//fenwick_update(BIT, end+1, 1);
		update(segtree, n, end, 1);
		it->end = end;
	}	
	
	for(auto it = vec.begin(); it<vec.end(); ++it){
		//it->nested_segments = fenwick_sum(BIT, it->end);
		it->nested_segments = sum(segtree, n, 0, (it->end)-1);
		//fenwick_update(BIT, (it->end)+1, -1);
		update(segtree, n, it->end, -1);
	}
	
	sort(vec.begin(), vec.end(), originalOrder);
	for(Segment segment : vec)
		cout<<segment.nested_segments<<endl;
	
	
	

    return 0;
}