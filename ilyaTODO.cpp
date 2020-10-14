#include <iostream>
#include <vector>

/*
	Execution time on G4G: 
	
	Correctness:
		
	Time complexity:
			
	Space complexity:
		
*/

&vector compute prefixes(vec){
	vec out;
	out.reserve(vec.size());
	currentSum = 0;
	for(it = vec.begin(); it <vec.end()-1, ++i){
		currentSum += vec[i] == vec[i+1];
		out.pushback(currentSum)
	}
	out.pushback(currentSum;)
}

int query(vector prefixes, int x, int y){//with x<y
	if(x==0)
		return prefiex[y]
	else
		return prefixes[y]-prefixes[x-1]
}
