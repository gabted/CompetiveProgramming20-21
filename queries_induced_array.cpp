#include <iostream>
#include <vector>
#include <limits>
using namespace std;

/*
	Correctness:
		
	Time complexity: O(n)
			
	Space complexity: O(n), to store already_seen values
		
*/

int main() {

    std::vector<int> vec;
    std::vector<int> already_seen;
	int n {};
	
	//collect data
	std::cin >> n;
	vec.reserve(n);
	for (int i {}; i < n; ++i) {
		int x {};
		std::cin >> x;
		vec.push_back(x);
	}
	
	//elaborate data
	already_seen = vector<int>(n+1, 0);
	bool foundN;
	int current_minimum = std::numeric_limits<int>::max();
	for(int i = 0; i<n; ++i){
		if(i > 0){
			if(vec[i] < vec[i-1])	//se è un valore discendente, aggiorno
				current_minimum = min(current_minimum, vec[i]);
			else if(vec[i] == vec[i-1]){
				continue;
			}	
		}
			//else vec[i] == vec[i-1], do nothing
		if(vec[i] > current_minimum && already_seen[vec[i]]){	//se è un valore ascendente, controllo non sia già visto
			cout << "N"<<endl;
			return 0;
		}
		foundN = foundN || (vec[i] == n);
		already_seen[vec[i]] = 1;
		}
	if(!foundN)
		cout << "N"<< endl;
	else
		cout << "Y"<< endl;
		
	

    return 0;
}