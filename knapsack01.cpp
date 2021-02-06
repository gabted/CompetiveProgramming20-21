#include <iostream>
#include <vector>
using namespace std;

/*
	Execution time on SPOJ: 0.01
		
	Time complexity: O(ns)
			
	Space complexity: O(ns)
		
*/

int main() {
	int s {};
	int n {};

	//collect data
	std::cin >> s;
	std::cin >> n;
	int *size = new int[n];
	int *value = new int[n];
	for (int i {}; i < n; ++i) {
		std::cin >> size[i];
		std::cin >> value[i];
	}
	
	//elaborate data
	
	int** A = new int*[n+1];
	//first row
	A[0] = new int[s+1];
	for(int j = 0; j<=s; ++j)
		A[0][j] = 0;
	//other rows
	for(int i = 1; i <=n; ++i){
		A[i] = new int[s+1];
		A[i][0] = 0;
	}
	
	//fill matrix
	for(int i = 1; i<= n; ++i){
		for(int j = 1; j<= s; ++j){
			if(size[i-1] > j)
				A[i][j] = A[i-1][j];
			else
				A[i][j] = max(A[i-1][j], value[i-1]+A[i-1][j-size[i-1]]);
		}
	}
	
	 /*for(int i = 0; i<= n; i++){
        for(int j = 0; j<= s; ++j)
            std::cout<<A[i][j]<<" ";
        cout <<endl;
    }*/
	
	std::cout << A[n][s];
	
    return 0;
}