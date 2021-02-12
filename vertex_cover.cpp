#include <iostream>
#include <vector>
using namespace std;

/*
	Execution time on SPOJ: 0.09s
	
	Correctness:
        This algoritm computes for each subtree, via a depth first visit,
		how big is the minimum vertex cover. When visiting a node x, we store
		into C[x] the minimum vertex cover if x is chosen, and into NC[x] the
		minimum vertex cover i x is not chosen. Starting the recursive DF visit from
		node 1, the answer will be min(C[i], NC[i]).
		
	Time complexity: O(n)
        It does a DF visit
			
	Space complexity: O(n)
        It stores the adjacency lists and the memoized values
		
*/

int n;
vector<int>* adj;
int* C;
int* NC;

//find the vertex cover of subtree rooted in x, coming from parent p
void find_cover(int x, int p){
    C[x] = 1;
    NC[x] = 0;
    for(auto child : adj[x])
        if(child != p){
            find_cover(child, x);
            C[x] += min(C[child], NC[child]);	//if x is chosen, we can select the best vertex cover for the subtrees
            NC[x] += C[child];	//if x is not chosen, we require that all the children are choonen.
        }
}

int main() {
    //collect data
    std::cin >> n;
    adj = new vector<int>[n+1];
    C = new int[n+1];
    NC = new int[n+1];
    for (int i {}; i < n-1; ++i) {
        int x {};
        int y {};
        std::cin >> x;
        std::cin >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    //elaborate data
    find_cover(1, -1);	//node 1 has no parent
    cout << min(C[1], NC[1]);

    return 0;
}