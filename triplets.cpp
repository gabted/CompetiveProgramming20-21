#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

template<class T>
class SumSegTree{
	private:
		int n{};
		int size{};
		T *tree{};
		//T *copyTree{};
		
		int left_child(int index){
			return 2*index+1;
		}
		int right_child(int index){
			return 2*index+2;
		}
		
		//fills the subtree rooted in "root", representing
		//the range [start, end]	
		void build_rec(int root,int start,int end){
			if(start == end)
				cin >> tree[root];
			else{	
				int mid = (start + end)/2;
				build_rec(left_child(root), start, mid);
				build_rec(right_child(root), mid+1, end);
				tree[root] = 
					tree[left_child(root)] + tree[right_child(root)];
			}
		}
		
		//walks the tree and adds value to index and all its ancestors
		void update_rec(int root, int start, int end, int index, T value){
			if(start == end){
				tree[root] += value;
			}
			else{
			tree[root] += value;
			int mid = (start + end)/2;
			if(index <= mid)
				update_rec(left_child(root), start, mid, index, value);
			else
				update_rec(right_child(root), mid+1, end, index, value);
			}
		}
		
		//gets the sum of the elements in [qstart, qend]
		T sum_rec(int root, int seg_start, int seg_end, int q_start, int q_end){
			if(q_start <= seg_start && seg_end <= q_end)	//if [segstart, segend] is inside the query
				return tree[root];
			else if(seg_end < q_start || q_end < seg_start)	//if [segstart, segend] is outside the query
				return 0;
			else{		//if [segstart segend] is partially inside the query		
				int mid = (seg_start + seg_end)/2;
				return sum_rec(left_child(root), seg_start, mid, q_start, q_end) 
					+ sum_rec(right_child(root), mid+1, seg_end, q_start, q_end);
			}
		}
		
	public:
		//allocates and initializes the tree reding n values from cin
		SumSegTree(int number_of_elements){
			n = number_of_elements;
			int h = (int) ceil(log2(number_of_elements));
			size = 2*(int)pow(2, h) - 1;
			tree = new T[size]{};
			//copyTree = new T[size]{};
			//build_rec(0, 0, n-1);	
		}
		
		//adds value to th element index-th value (in the original array of n elements)
		void update(int index, T value){
			update_rec(0, 0, n-1, index, value);
		}
	
		//gets the sum of elements in [qstart, qend]
		T sum(int q_start, int q_end){
			return sum_rec(0, 0, n-1, q_start, q_end);
		}
		
		void print(){
			for(int i = 0; i < size; ++i)
				cout<<tree[i]<<endl;
		}
};	//end class





int main(){
	int n {};
	cin >> n;
	SumSegTree<int64_t> Ks(n+1);
	SumSegTree<int64_t> Js(n+1);
	
	std::vector<int> vec;
	for (int i {}; i < n; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
	
	int64_t total {};
	for(int i {n-1}; i>=0; --i){
		if(i <= n-3){
			//process i
			total += Js.sum(vec[i]+1, n);
		}
		if(i <= n-2){
			//process j
			int64_t ks = Ks.sum(vec[i]+1, n);
			Js.update(vec[i], ks);
		}
		Ks.update(vec[i], 1);
	}
	cout<<total;


}