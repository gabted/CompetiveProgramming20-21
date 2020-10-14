#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
/*
	Execution time on G4G: 1045ms
	
	Correctness:
		The algorithm makes use of the following proprieties:
		-If t, the sum of the element of the array is not divisible by 3, the solution is 0
		-If t, the sum of the element of the array is divisible by 3, for each of the 3 "segment" of a solution,
		 a=[0, i], b=[i+1, j], c=[j+1, n-1] holds that the sum of the element in a segment is t/3, and is an integer
		-If S is the array of prefix sums, S[i] = t/3 and S[j] = t*2/3
		
	Time complexity: O(n)
			
	Space complexity: O(n)
		
*/

uint64_t count_number_of_ways(std::vector<int> &vec, int64_t total){
	if(total % 3 != 0)
		return 0;
	else{
		//	build the prefix-sums array
		int n = vec.size();
		std::vector<int64_t> sums;
		sums.reserve(n);
		int64_t partial_sum {};
		for(int el : vec){
			partial_sum += el;
			sums.push_back(partial_sum);
		}
		
		/* 	Scans the array from let to right, in order to find all the i such that
			sums[i] == total/3, i.e. all the i that could possibly be the "left separator", 
			which divides the first segment from the second
			This first scan increases counter also if it find sums[n-2] == total/3.
			This postion is not a valid "left separator", cause n-2 is the second to last 
			element of the array, and if I consider the first segment ending at n-2, 
			there's no space remaining for the second and third segment.
			This incorrect increase is not a problem, because counter will bedecreased in the second scan.
		*/
		uint64_t counter {};
		for(auto it=sums.begin(); it<sums.end()-1; ++it)
			if(*it == total/3)
				++counter;
		
		/*	Scans the array from right to left, in order to find all the i such that
			sums[i] == total*2/3, i.e. all the i that could possibly be the "right separator", 
			which divides the second segment from the third.
			In order to compute the result, i.e, the total number of possible pairs of
			left and right separators, i should add to result, for each "r" right separator, all
			the "l" left separators compatible with r. (l is compatible with r if l<r). To do so,
			every time I find an "l", i decrease the number of compatible separators.			
		*/
		uint64_t result {};
		for(auto it = sums.rbegin()+1; it<sums.rend(); ++it){
			if(*it == total/3)
				--counter;
			if(*it == 2*total/3)
				result += counter;
		}
		return result;
	}
}

int main() {
	//collect data
    std::vector<int> vec;
	int n {};
	cin >> n;
	vec.reserve(n);
	int64_t totalSum {};
	for (int i {}; i < n; ++i) {
		int x {};
		cin >> x;
		totalSum += x;
		vec.push_back(x);
	}
	
	//elaborate data
	cout << count_number_of_ways(vec, totalSum);
	
	//clear data
	vec.clear();

    return 0;
}