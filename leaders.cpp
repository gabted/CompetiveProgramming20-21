#include <iostream>
#include <vector>
#include <algorithm>

/*

Running time on Geeks4Geeks: 0.94

The code searches for the suffix-maximum by scanning the array in reverse order.
I used some lambda expression to experiment withthem, but I'll stop use them, to improve readability

*/

void leaders(std::vector<int> const& vec) {
    std::vector<int> leaders; // accumulate leaders to print them in original order
    leaders.reserve(vec.size());
    
	//computes the leaders, in reverse order
	int max = vec.back();
    leaders.push_back(max); // last element is always a leader
	auto check_leader = [&](const int &n){if(n >= max){max = n; leaders.push_back(max);}};
	std::for_each(vec.rbegin()+1, vec.rend(), check_leader);
	
	//print the leaders, in the original order of the data
	std::for_each(leaders.rbegin(), leaders.rend(), [](int &n){std::cout<<n<<" ";});
    std::cout << std::endl;
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
		leaders(vec);
		
		//clear data
        vec.clear();
    }

    return 0;
}