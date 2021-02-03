// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends

/*
	Execution time on G4G: 0.91s
	
	Correctness: 
		Our desired function, which returns the minimum number
		of jumps needed to reach the end, is easily defined as
		f(n-1) = 0 (where A[n-1] is the last element of the array A)
		f(i) = 1 + min_{j in Reach(i)}(f(j)), where Reach(i) are all
		the positions reachable from i, i.e. {i+1, i+2, .., i+A[i]}
		
		In order to compute efficiently this function, we can memoize its
		results storing f(i) for each i, in an appropriate data structure.
		The answer of the problem will be simply f(0).
		
		We can use a MinSegTree to execute easily insertion and RMQ,
		and, proceding backward, we fill this segtree with f(i)
		
	Time complexity: O(nlogn)
		for each element we execute a logn RMQ. Due to the fact that,
		once inserted, a value is never changed, we could also use a sparse table
		approach, but building, for each element, a row of the sparse table would
		also require O(logn).
			
	Space complexity: O(n), for the segtree
		
*/

//global value for infinite value, such that
//ForAll x, min(x, inf) = inf
int inf = numeric_limits<int>::max();

template<class T>
class MinSegTree{
	private:
		int n{};
		int size{};
		T *tree{};
		
		int left_child(int index){
			return 2*index+1;
		}
		int right_child(int index){
			return 2*index+2;
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
		
		//gets the min of the elements in [left, right] inside 
		T min_rec(int root, int seg_start, int seg_end, int q_start, int q_end){
			if(q_start <= seg_start && seg_end <= q_end)	//if [segstart, segend] is inside the query
				return tree[root];
			else if(seg_end < q_start || q_end < seg_start)	//if [segstart, segend] is outside the query
				return inf;
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
		}
		
		//adds value to the element index-th value (in the original array of n elements)
		void update(int index, T value){
			update_rec(0, 0, n-1, index, value);
		}
		
		//gets the sum of elements in [qstart, qend]
		T get_min(int q_start, int q_end){
			//if q_end is bigger then n-1, search up to n-1 instead
			return min_rec(0, 0, n-1, q_start, min(q_end, n-1));
		}
		void print(){
			for(int i = 0; i < size; ++i)
				cout<<tree[i]<<endl;
		}
		
};	//end class


// Function to return minimum number of jumps to end of array
int minJumps(int arr[], int n){
    // Your code here
    MinSegTree<int> tree(n);
	
	//scan backward, skipping the last element
	for(int i = n-2; i>=0; --i){
		//search the best next jump to do
		//i.e., search the element with minimum distance from the end,
		//within the "reach" of A_i (that is [i, i+A_i])
		int minJump = tree.get_min(i+1, i+arr[i]);
		
		//if A_i = 0 or if A_i can reach only zero values, return inf
		//cause are needed "infinite" steps to reach end
		if(arr[i] == 0 || minJump == inf)
			tree.update(i, inf);
		else
			tree.update(i, 1+minJump);
	}
	
	int answer = tree.get_min(0, 0);
	if(answer == inf)
	    //there are no possible paths to the end, the minimum distance is infinite
	    return -1;
	else
	    return answer;
}

// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,i,j;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
            cin>>arr[i];
            
        cout<<numeric_limits<int>::max()+1<<endl;
    }
    return 0;
}
  // } Driver Code Ends