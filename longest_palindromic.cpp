#include <iostream>
#include <algorithm>
using namespace std;
/*
	Execution time on g4g: 0.34s
	
	Correctness:
		The longest palindromic subsequence is reduced to the longest common subsequence
		problem between s an s reversed.
		
	Time complexity: O(n^2)
			
	Space complexity: O(n*^2
		
*/

int lcs(int x, int y, string s1, string s2){
    
    int** A = new int*[x+1];
    
    //first row
    A[0] = new int[y+1];
    for(int j = 0; j<=y; ++j)
        A[0][j] = 0;
    //other rows
    for(int i = 1; i <=x; ++i){
        A[i] = new int[y+1];
        A[i][0] = 0;
    }
    
    //fill matrix
    for(int i = 1; i<= x; ++i){
        for(int j = 1; j<= y; ++j){
            if(s1[i-1] == s2[j-1])
                A[i][j] = 1+A[i-1][j-1];
            else
                A[i][j] = std::max(A[i-1][j], A[i][j-1]);
        }
    }
    
   /* for(int i = 0; i<= x; i++){
        for(int j = 0; j<= y; ++j)
            std::cout<<A[i][j]<<" ";
        cout <<endl;
    }*/
    
    return A[x][y];
    
}

int main() {
	//code
	
	int num_test_cases;
    std::cin >> num_test_cases;

    string s;
    string t;
    for (int k {}; k < num_test_cases; ++k) {
        cin >> s;
        t = s;
        std::reverse(s.begin(), s.end()); 
        
        int n = s.length();
        cout <<lcs(n, n, s, t)<<endl;
		
    }
	return 0;
}