#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;

/*
	Execution time on codeforces: time limit exeeded on test 21
	
	Correctness: 
		This algorithm flattens the tree into an array, storing for eeach node the starting
		and ending point of the sequence on colors corresponding to that subtree.
		Then uses Mo algorithm to upgrade 2 data structures:
			-colorFrequency[c] says how frequent is a color, i.e. 
				how many occurencies are of the color c in the current range
			-colorsMoreFrequentThen[k] says how many colors are more frequent than k 
		
	Time complexity: O((n + q) sqrt n)
			
	Space complexity: O(n)
		
*/

struct Node {
	int color;
	vector<int> adj;	//adjacency list
	int left;
	int right;
};

struct Query {
	int l;
	int r;
	int k;

	int index;
	int result;
};

//#########global variables
int n;	//size of the tree
Node* nodes;	//tree
vector<int> flattened;	//flattened tree
int buckSize;
unordered_map<int, int> colorFrequency;
vector<int> colorsMoreFrequentThen;

//does a preorder visit, flattening the tree into flattened
void flatten(int root, int parent){	
	nodes[root].left = flattened.size();
	flattened.push_back(nodes[root].color);
	for(int el : nodes[root].adj)
		if(el != parent)
			flatten(el, root);
	nodes[root].right = flattened.size()-1;
}

//########functions to reorder queries
bool compare(Query &a, Query &b){
	int bucket_a = a.l / buckSize;
	int bucket_b = a.l / buckSize;
	if(bucket_a == bucket_b)
		return a.r < b.r;
	else
		return bucket_a < bucket_b;

	return true;
}
bool reorder(Query &a, Query &b){
	return a.index < b.index;
}

void print(){
	for(int i = 1; i <= n; i++){
		cout << "node "<<i<<":"<<endl;
		cout << "\tcolor: "<<nodes[i].color<<endl;
		cout << "\tadj: ";
		for(int el : nodes[i].adj)
			cout <<el<<", ";
		cout << "\n\tleft: "<<nodes[i].left<<" right: "<<nodes[i].right<<endl;
		cout<<endl;
	}
	
}

//############functiosn of Mo algorithm
void add(int p){
	int new_frequency = ++colorFrequency[flattened[p]];
	++colorsMoreFrequentThen[new_frequency];
}

void remove(int p){
	int new_frequency = --colorFrequency[flattened[p]];
	--colorsMoreFrequentThen[new_frequency+1];
}

int main() {
    //collect tree
    int m {};
	scanf(" %d%d", &n, &m);
	nodes = new Node[n+1];
	for(int i = 1; i <= n; ++i)
		scanf("%d", &(nodes[i].color));
    for (int i {}; i < n-1; ++i) {
        int x {};
        int y {};
        scanf(" %d%d", &x, &y);
        nodes[x].adj.push_back(y);
        nodes[y].adj.push_back(x);
    }
	
	//flatten tree
	flattened.push_back(0);	//dummy value
	flatten(1, 0);	//start a df visit with root 1
	
	//collect queries
    std::vector<Query> queries;
	queries.reserve(m);
	for (int i {}; i < m; ++i) {
		int root {};
		int k {};
		scanf("%d%d", &root, &k);
		queries.push_back({nodes[root].left, nodes[root].right, k, i, 0});
	}
	//sorting queries
	buckSize = sqrt(n);
	sort(queries.begin(), queries.end(), compare);
    
    //print();
	
	//execute queries
	colorFrequency.max_load_factor(0.25);
	//colorFrequency.rehash(n+1);
	colorFrequency.reserve(n+1);
	colorsMoreFrequentThen = vector<int>(n+1);
	int curr_l = 0;
	int curr_r = 0;
	for(int i {}; i<m; i++){
		Query &q = queries[i];
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
		
		
		if(q.k > n)
			queries[i].result = 0;
		else
			queries[i].result = colorsMoreFrequentThen[q.k];		
	}
	
	//sort and print
	sort(queries.begin(), queries.end(), reorder);
	for(auto q : queries)
		cout<<q.result<<endl;

    return 0;
}

/*
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3
*/