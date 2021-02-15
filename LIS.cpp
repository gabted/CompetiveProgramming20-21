/*
	Execution time on G4G: 0.28
	
	Correctness: the Algorithm was presented during the lesson
		
	Time complexity: O(nlogn)
			
	Space complexity: O(n)
		
*/

int longestSubsequence(int n, int a[])
{
    const int INF = std::numeric_limits<int>::max();
    vector<int> ends(n+1, INF);
    ends[0] = -1;   //dummy value
    int tempResult = 1; //the smallest increasing subsequence is always one
    for (int i = 0; i < n; i++) {
            int j = upper_bound(ends.begin(), ends.end(), a[i]) - ends.begin(); 
            if (!(ends[j-1] == a[i])){  //i do not want to insert a[i] if is already present in the previous slot
                ends[j] = a[i];
                tempResult = max(tempResult, j);
            }
    }

    return tempResult;
}