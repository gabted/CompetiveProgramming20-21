#include <iostream>
#include <vector>
#include <unordered_map>

/*
	Execution time on codeforces: 233ms
	
	Correctness:
		The algorithm scans the array visiting all the "legal" segment,
		i.e. all segment with at most k distinct values
		
	Time complexity: O(n)
		Allocating the map requires k costant time insertion, O(k)
		Each cycle of the loop could apparently coast O(n), but the overall execution
		time is infact limited to O(n), because every element is inserted and extracted
		at most one time.
			
	Space complexity: O(k)
		The insertions and deletions on the map keep the map costant in size, and so 
		the UnorderedMap is allocated at the begininning and never resized.
		
*/

void searchLongestKGood(std::vector<int> &vec, int k){
	//allocate map
	std::unordered_map<int, int> map;
	//as soon as the segmen reaches k+1 different values, it will
	//be shortened, so the map will never contain more than k+1 el
	map.reserve(k+1);
	
	//adds the first k element to map
	auto left = vec.begin();
	for(int i{}; i<k; ++i)
		++map[*(left+i)];
	auto right = vec.begin()+k-1;
	//now left points to the right extreme of the segment,
	//right to the right extreme
	
	//store the current value as prefix solution
	int best_segment = right-left;
	int best_right = right-vec.begin()+1;
	int best_left = left-vec.begin()+1;
	
	
	/*each cycle has three steps:
		-advancing the right pointer
		-advancing the left pointer (if needed) such as
		 map cotains at most k element
		-confronting the current valid segment with the best found so far*/	
	while(right < vec.end()-1){
		//increase right and add element
		++right;
		++map[*right];
		
		while(map.size() > k){  //increase left
			//deletes one left occurence from map
			--map[*left];
			//deletes the left key if empty
			if(map[*left] == 0)
				map.erase(*left);
			//increases left
			++left;
		}
		//confront the newfound valid segment with the previous best
		if(right-left > best_segment){
			best_segment = right-left;
			best_right = right-vec.begin()+1;
			best_left = left-vec.begin()+1;
		}
	}
	
	std::cout<<best_left<<" "<<best_right<<std::endl;
	
}

int main() {

    std::vector<int> vec;
	//collect data
	int n {}, k {};
	std::cin >> n;
	std::cin >> k;
	vec.reserve(n);
	for (int i {}; i < n; ++i) {
		int x {};
		std::scanf("%d", &x);
		vec.push_back(x);
	}
	
	//elaborate data
	searchLongestKGood(vec, k);
	
	//clear data
	vec.clear();

    return 0;
}