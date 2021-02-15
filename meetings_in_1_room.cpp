/*
	Execution time on g4g: 0.57ms
	
	Correctness:
		The algorithm was presented in class
		
	Time complexity:  O(nlogn)
			
	Space complexity: O(n)
		
*/



int maxMeetings(int start[], int end[], int n) {
    // Your code here
    vector<int> meetings = vector<int>(n);
    std::iota(meetings.begin(), meetings.end(), 0);
    std::sort(meetings.begin(), meetings.end(), [&](int i, int j) {return end[i] < end[j]; });
    int current_end_time = -1;
    int total = 0;
    for(auto m : meetings)
        if(start[m] > current_end_time){
            ++total;
            current_end_time = end[m];
        }
    return total;
}