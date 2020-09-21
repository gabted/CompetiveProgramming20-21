#include <iostream>
#include <vector>
#include <algorithm>

/*
	Execution time on codeforce: 577 ms 
	
	Correctness:
		This algorithm implements a greedy strategy wich is complete according to the following reasons:
		if the players a and b possesses the best possible team of all, they have no reason to choose any other
		team member. Consequently, a and b can be removed from the problem, since they aren't elegible player anymore.
		The same reasoning applyes to the second-best possible team, and so on, given that the non optimal team referring
		to already paired players should be discarded.
		
	Time complexity: O(nlogn) in the worst case
		The input is organized in a heap, by a call of std::make_heap which runs in linear time (only the first half 
		of the vector needs to be heapified). By extracting the best rated teams one after the other, we got slightly better
		time ccomplexity then simply sorting the input. Sorting in fact would cost O(n*logn) moves, while heapifying and extracting
		cost O(n + log(n) + log(n) + 1og(n-1) + ...). If the input is sorted in the worst possible way, the complexity will be O(nlogn), 
		but that's not the averag case.
		
	Space complexity: O(sqrt(n))
		the only auxiliary data structure used is a vector to store the already computed output. With n+1 players,
		the input consist of Tn different ratings, where Tn is the n-th Triangular Number, and so is quadratic with respect to n.		
*/

struct Team{
	int rating;
	int a;
	int b;
};

bool compareTeam(Team a, Team b){
	return a.rating < b.rating;
}

void make_n_teams(std::vector<Team> &data, int n){
	//build output vector
	std::vector<int> output(2*n, 0); //initilizes a vector of all zeros
	
	//build max-heap of struct 
	std::make_heap(data.begin(), data.end(), compareTeam);
	
	//extracts the best teams one after the other, discarding them if 
	//the corrisponding player are already assigned
	int assigned_teams {0};
	while(assigned_teams < n){
		//extract root of the heap
		Team current_max = data.front();
		std::pop_heap(data.begin(), data.end(), compareTeam);
		data.pop_back();
		
		//tries to assign players to each other, unless they're already assigned
		if(output.at(current_max.a-1) == 0 && output.at(current_max.b-1) == 0){
			output.at(current_max.a-1) = current_max.b;
			output.at(current_max.b-1) = current_max.a;
			++assigned_teams;
		}
	}
	
	//prints the ordered output
	for(int n : output)
		std::cout << n <<" ";
}

int main() {
	int n {};
	std::cin >> n;
	
	//allocate vector
	std::vector<Team> data;
	int number_of_rows = 2*n -1;
	int number_of_teams = number_of_rows*(number_of_rows+1)/2; //formula for triangular number
	data.reserve(number_of_teams);
	
	//fetch data, storing them in struct inside a vector
	for(int i {2}; i<=2*n; ++i){
		for(int j {1}; j<i; ++j){
			int rating {};
			std::cin >> rating;
			data.push_back({rating, j, i});
		}
	}
	
	//compute teams
	make_n_teams(data, n);
	
	return 0;
}