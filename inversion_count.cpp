#include <iostream>
#include <vector>
/*
	Execution time on SpOJ: 0.14
	
	Correctness:
		This algorithm was explained in class
		
	Time complexity:O(nlogn)
			
	Space complexity:O(n)
		
*/

long long merge(std::vector<int> &V, int start, int mid, int end){
	
	long long inversions {};
	//alloco array copia
	std::vector<int> R(mid-start+1);
	std::vector<int> L(end-mid);
	for(int i{}; i<R.size(); ++i)
		R[i] = V[start+i];
	for(int i{}; i<L.size(); ++i)
		L[i] = V[mid+1+i];
	
	//merging
	//r cyles over R, l over L and v over V
	int r {}, l{}, v{start};
	while(r<R.size() && l<L.size()){
		if(R[r] < L[l])
			V[v++] = R[r++];
		else{
			V[v++] = L[l++];
			inversions += mid-start-r+1;
		}
	}
	
	//copies remaining element of R, if present
	while (r < R.size()) 
        V[v++] = R[r++]; 

	//copies remaining element of L, if present
	while (l < L.size()) 
        V[v++] = L[l++];
	
	return inversions;
}

long long count_inversion(std::vector<int> &vec, int start, int end){
	if(start < end){
		long long out {};
		int mid = (start+end)/2;
		out += count_inversion(vec, start, mid);
		out += count_inversion(vec, mid+1, end);
		out += merge(vec, start, mid, end);
		return out;
	}
	else
		return 0;
}


int main() {

    int num_test_cases {};
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int k {}; k < num_test_cases; ++k) {
		//collect data
		int n {};
        std::cin >> n;
        vec.reserve(n);
        for (int i {}; i < n; ++i) {
            int x {};
            std::cin >> x;
            vec.push_back(x);
        }
        
		//elaborate data
		std::cout<<count_inversion(vec, 0, n-1)<<std::endl;
		//for(int el : vec)
			//std::cout<<el<<" ";
		//std::cout<<std::endl;
		
		//clear data
        vec.clear();
    }

    return 0;
}