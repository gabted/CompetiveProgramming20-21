/*
	Execution time on G4G: 0.02s
	
	Correctness: the Algorithm was presented during the lesson
		
	Time complexity: 
			
	Space complexity: 
		
*/


int LongestBitonicSequence(vector<int>nums)
	{
	    const int INF = std::numeric_limits<int>::max();
	    int n = nums.size();
        vector<int> LIS(n);
        vector<int> LDS(n);
        vector<int> ends(n+1, INF);
        ends[0] = -1;   //dummy value
	    
	    //calculate ad store values of LIS
        int tempResult = 1; //the smalelst increasing subsequence is always one
        for (int i = 0; i < n; i++) {
                int j = upper_bound(ends.begin(), ends.end(), nums[i]) - ends.begin();    //
                if (!(ends[j-1] == nums[i])){  //i do not want to insert nums[i] if is already present in the previous slot
                    ends[j] = nums[i];
                    tempResult = max(tempResult, j);
                }
            LIS[i] = tempResult;
            //cout<<i<<" "<<tempResult<<endl;
        }
        
        //restor work vector
        for(auto it = ends.begin()+1; it<ends.end(); ++it)
            *it = INF;
        tempResult = 1; //the smalelst increasing subsequence is always one
        
        //calculate and store value of LDS
        for (int i = n-1; i >= 0; i--) {
                int j = upper_bound(ends.begin(), ends.end(), nums[i]) - ends.begin();    //
                if (!(ends[j-1] == nums[i])){  //i do not want to insert nums[i] if is already present in the previous slot
                    ends[j] = nums[i];
                    tempResult = max(tempResult, j);
                }
            LDS[i] = tempResult;
            //cout<<i<<" "<<tempResult<<endl;
        }
        
        //find longest bitonic
        int output = 1;
        for(int i = 0; i<n; ++i)
            output = max(output, LIS[i]+LDS[i]-1);
        return output;
	}