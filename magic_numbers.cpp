#include <iostream>
#include <vector>
using namespace std;

/*
	Execution time on codeforces: 62ms
	
	Correctness:
		This algorithm searches for the longes accepted prefix (144, 14 or 1),
		and, if found, jumps greedily after the prefix. Doing so we do not lose
		any correct solution, because no character on the longest accepted prefix
		could be the starting point of a new accepted prefix.
		
	Time complexity: O(n)
			
	Space complexity: O(1)
		
*/

int main() {

	string s;
	std::cin >> s;
	int n = s.length();
	int i {};
	while(i<n){
		 if(s[i] == '1'){
			 if(i<n-1 && s[i+1] == '4'){
				 if(i<n-2 && s[i+2] == '4'){
					 i += 3;
					 continue;
				 }
				 i += 2;
				 continue;
			 }
			 ++i;
			 continue;
		 }
		 
		 cout << "NO";
		 return 0;
	}
	cout << "YES";
        

    return 0;
}