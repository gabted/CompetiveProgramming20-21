
/*
	Execution time on G4G: 0.29s
	
	Correctness: 
		This a simple application of the subset-sum dynamic programming algorithm.
		Tot is even, and exists a subset with sum tot/2, thene the lement outside the 
		subset also sum up to tot/2.
		
	Time complexity: O(n*k), where k is O(sum of all elements)
			
	Space complexity: O(n*k), where k is O(sum of all elements)
		
*/


int equalPartition(int N, int arr[]){
        int tot = accumulate(arr, arr+N, 0);
        if(tot % 2 == 1)
            return 0;
        else{
            int half = tot/2;
            int** A = new int*[N+1];
        
            //first row
            A[0] = new int[half+1];
            A[0][0] = 1;
            for(int j = 1; j<=half; ++j)
                A[0][j] = 0;
            //other rows
            for(int i = 1; i <=N; ++i){
                A[i] = new int[half+1];
                A[i][0] = 1;
            }
            
            //fill matrix
            for(int i = 1; i<= N; ++i){
                for(int j = 1; j<= half; ++j){
                    int desired_value = j-arr[i-1]; //if we want to include this element, 
                                                    //we need  a subset (in the prefix) with value desired_value
                    A[i][j] = A[i-1][j] || (desired_value >= 0 && A[i-1][desired_value]);
                }
            }
            
            return A[N][half];
        }
    }