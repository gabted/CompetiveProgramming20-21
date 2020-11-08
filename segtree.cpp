#include <iostream>
#include <vector>
#include <math.h>
using namespace std;



int main(){
	int n {};
	cin >> n;
	
	vector<int64_t> tree = build_segment_tree(n);
	update(tree, n, 2, 5);
	update(tree, n, 3, 5);
	int left {}, right {};
	cin >> left;
	cin >> right;
	cout<<sum(tree, n, left, right)<<endl<<endl;
	
	for(auto el : tree)
		cout << el << endl;
	

}

/* 	void update(index, value){
		caiinare lungo l'albero, aggiungendo value 
		tutti i nodi interni fino a index.
	} */