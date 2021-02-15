#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <limits>
#include <cstring>
using namespace std;

/*
	Execution time on G4G: 1310ms
	
	Correctness:
			This algorithm uses a Persistent Segment Tree to implement dymanic RMQ,
			and splits every circular rmq in two different, normal-ordered rmq.
			
	Time complexity: O(n + mlogn), to construct the tree and to do the queries
			
	Space complexity: O(n)
		
*/

template<class T>
class MinSegTree{
	private:
		int n{};
		int size{};
		T *tree{};
		T *lazy{};
		
		int left_child(int index){
			return 2*index+1;
		}
		int right_child(int index){
			return 2*index+2;
		}
		
		void apply_pending_update(int root ,int seg_start, int seg_end){
			if(lazy[root] != 0){
				tree[root] += lazy[root];
				if(seg_start != seg_end){
					lazy[left_child(root)] += lazy[root];
					lazy[right_child(root)] += lazy[root];
				}
				lazy[root] = 0;
			}
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
				tree[root] = min(tree[left_child(root)],
					tree[right_child(root)]);
			}
		}
		

		void update_rec(int root, int start, int end, int index, T value){
			if(start == end){
				tree[root] += value;
			}
			else{
				int mid = (start + end)/2;
				if(index <= mid)
					update_rec(left_child(root), start, mid, index, value);
				else
					update_rec(right_child(root), mid+1, end, index, value);
				tree[root] = min(tree[left_child(root)],
						tree[right_child(root)]);
			}
		}
		
		void range_update_rec(int root, int seg_start, int seg_end, int u_start, int u_end, T value){
			//i'm visiting a node, so i apply the pending updates
			apply_pending_update(root, seg_start, seg_end);
			
			if(seg_end < u_start || u_end < seg_start)	//if [segstart, segend] is outside the update
				{}											//do nothing
			else if(u_start <= seg_start && seg_end <= u_end){	//if [segstart, segend] is inside the update
				tree[root] += value;							//update current value, and lazy update children
				if(seg_start != seg_end){
					lazy[left_child(root)] += value;
					lazy[right_child(root)] += value;
				}
			}
			else{												//if [segstart segend] is partially inside the update		
				int mid = (seg_start + seg_end)/2;				//update both hildren and recalculate current value
				range_update_rec(left_child(root), seg_start, mid, u_start, u_end, value);
				range_update_rec(right_child(root), mid+1, seg_end, u_start, u_end, value);
				tree[root] = min(tree[left_child(root)],
						tree[right_child(root)]);
			}
			
		}
		
		//gets the min of the elements in [left, right] inside 
		T min_rec(int root, int seg_start, int seg_end, int q_start, int q_end){
			//i'm visiting a node, so i apply the pending updates
			apply_pending_update(root, seg_start, seg_end);
			
			if(q_start <= seg_start && seg_end <= q_end)	//if [segstart, segend] is inside the query
				return tree[root];
			else if(seg_end < q_start || q_end < seg_start)	//if [segstart, segend] is outside the query
				return numeric_limits<T>::max();
			else{		//if [segstart segend] is partially inside the query		
				int mid = (seg_start + seg_end)/2;
				T minleft = min_rec(left_child(root), seg_start, mid, q_start, q_end);
				T minright = min_rec(right_child(root), mid+1, seg_end, q_start, q_end);
				return min( minleft, minright);
			}
		}
		
	public:
		//allocates and initializes the tree reding n values from cin
		MinSegTree(int number_of_elements){
			n = number_of_elements;
			int h = (int) ceil(log2(number_of_elements));
			size = 2*(int)pow(2, h) - 1;
			tree = new T[size]{};
			lazy = new T[size]{};
			build_rec(0, 0, n-1);	
		}
		
		//adds value to the element index-th value (in the original array of n elements)
		void update(int index, T value){
			update_rec(0, 0, n-1, index, value);
		}
		
		//adds value to all elements in [start end]
		void range_update(int start, int end, T value){
			range_update_rec(0, 0, n-1, start, end, value);
		}
		
		void circular_range_update(int start, int end, T value){
			if(start <= end)
				range_update(start, end, value);
			else{
				range_update(start, n-1, value);
				range_update(0, end, value);		
			}
		}
		
		//gets the sum of elements in [qstart, qend]
		T get_min(int start, int end){
			return min_rec(0, 0, n-1, start, end);
		}
		
		T circular_get_min(int start, int end){
			if(start <= end)
				return get_min(start, end);
			else{
				return min(get_min(start, n-1), get_min(0, end));		
			}
		}
		
		void print(){
			for(int i = 0; i < size; ++i)
				cout<<tree[i]<<endl;
		}
		
};	//end class

int main() {

    
	//collect data
	int n {}, k{};
	std::cin >> n;
	MinSegTree<int64_t> tree(n);
	
/* 	cout<<tree.circular_get_min(3, 0)<<endl;
	tree.circular_range_update(3, 0, -1);
	cout<<tree.circular_get_min(0, 1)<<endl;
	cout<<tree.circular_get_min(2, 1)<<endl; */
	
	std::cin >> k;
	char line[30];
	cin.getline(line, 30);	//reads the line containing k
	int start {}, end {}, value {};
	char *temp;
	for(int i = 0; i<k; ++i){
		cin.getline(line, 30);
		start = atoi(strtok(line, " "));
		end = atoi(strtok(NULL, " "));
		temp = strtok(NULL, " ");
		if(temp == NULL)
			cout<<tree.circular_get_min(start, end)<<endl;
		else{
			value = atoi(temp);
			tree.circular_range_update(start, end, value);
		}
	}

    return 0;
}