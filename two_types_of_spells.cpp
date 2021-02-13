#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*
	Execution time on codeforces: 1107 ms
	
	Correctness:
		Let k be the number of lightning spells. THis algorithm divides the spells currently inserted
		into two set, high and log. High contains the top k spells (w.r.t. power), and grows and shrinks
		when k changes (i.e. when lightning spells are inserted or deleted). 
		
		Whith these definition, we cane prove the following lemma:
		Lemma: low contains only fire spells <=> high contains only lightning spells
			=> verse: high has size k, possibly 0, and all the lightning spells are in high,
				cause they can't be in low. But the lightnng spells are k, and so high cannot contain
				any fire spell.
			<= verse: There are k lightning spells and they are all in high.
		From this follow these corollaries:
		Corollary 1) low is empty => high contains only lightning spells (possibly 0)
		Corollary 2) high contains also firespells => low is not empty (the inversion of cororllary one)
		
		In a normal situation, the k lightning spells can duplicate the power of all the spells in high,
		and the total output equals "sum_of_low + 2*sum_of_high", 
		where sum_of_x is the sum of the damage of all spells in x.
		But we have to consider also the edge case where high contains only lightning spells.
		In this case, the smallest lightning spell should not be doubled, because is the start
		of a chain of lighning spells. The biggest lightning spell, instead, can double the biggest
		spell in low (which is a firespell). So the total output equals 
		"sum_of_low + 2*sum_of_high - min_of_high + max_of_low"
		
	Time complexity: O(nlogn)
		each operation requires a costant number of get_min and get_max into low and
		high, which are done in logarithmic time thanks to the balanced BST implementation of std::set
	
	Space complexity: O(), to store the two sets.
		
*/

struct spell{
	bool isLight;
	int64_t power;
};

bool operator<(const spell &a, const spell &b)
{
	return a.power < b.power;
}

/*void print(set<spell>& l, set<spell>& h){
	cout << "low: "<< endl;
	for(auto it = l.begin(); it != l.end(); ++it)
		cout <<"\t"<<it->isLight<<" "<<it->power<<endl;
	
	cout << "\n\nhigh: "<< endl;
		for(auto it = h.begin(); it != h.end(); ++it)
		cout <<"\t"<<it->isLight<<" "<<it->power<<endl;
	cout <<"k= "<<h.size()<<endl;
}*/

int main() {

	int n {};
	cin >> n;
	
	//variables for high, i.e. the set of top k elements
	int k {};	//|high|, number of lightning spells
	std::set<spell> high;
	int64_t high_sum {};
	int num_of_lightning_high {};	//this counter is needed to distinguish the cases where high contains only lightning spells
	
	//variables for low, i.e. the spells not in high
	std::set<spell> low;
	int64_t low_sum {};
	
	int64_t result {};
    for (int i {}; i<n; ++i) {
		//collect data
		bool isLight;
		int64_t power;
        cin >> isLight;
        cin >> power;
		
		if(power > 0){	//inserton
			if(!isLight){	//firespell
				if(high.empty()){	//insert firespell into low
					low_sum += power;
					low.insert({isLight, power});
				}
				else if(high.begin()->power > power){	//insert firespell into low
					low_sum += power;
					low.insert({isLight, power});
				}
				else{	//insert firespell into high, which is not empty
					high_sum += power;
					high.insert({isLight, power});
					//pop minimum from high and put into low
					low_sum +=  high.begin()->power;
					low.insert(*high.begin());
					num_of_lightning_high -= high.begin()->isLight;
					high_sum -= high.begin()->power;
					high.erase(high.begin());
				}
			}
			else{	//insert lightning spell
				++k;
				if(high.empty() || high.begin()->power > power){	//insert lightspell into low
					low_sum += power;
					low.insert({isLight, power});
					//pop max from low and put into high, because high must increase
					num_of_lightning_high += low.rbegin()->isLight;
					high_sum += low.rbegin()->power;
					high.insert(*low.rbegin());	//low.rbegin() and --low.end() point to the max of low
					low_sum -= low.rbegin()->power;
					low.erase(--low.end());
				}
				else{	//insert lightspell into high, wich increase without modifing low
					num_of_lightning_high++;
					high_sum += power;
					high.insert({isLight, power});
				}
			}
		}//end insertion
		else{	//deletion
			power = -power;
			if(!isLight){	//delete firespell
				if(low.count({isLight, power})){	//delete firespell from low
					low_sum -= power;
					low.erase({isLight, power});
				}
				else{	//delete firespell from high
					//thanks to corollary two, we know that low is not empty
					high_sum -= power;
					high.erase({isLight, power});
					//pop max of low and put into high
					num_of_lightning_high += low.rbegin()->isLight;
					high_sum += low.rbegin()->power;
					high.insert(*low.rbegin());
					low_sum -= low.rbegin()->power;
					low.erase(--low.end());
				}
			}
			else{	//delete lightning spell
				k--;
				if(low.count({isLight, power})){	//delete lightspell from low
					low_sum -= power;
					low.erase({isLight, power});
					//pop min from high an put into low
					low_sum += high.begin()->power;
					low.insert(*high.begin());	//we know that high was not empty, cause this ligthning was present (in low)
					num_of_lightning_high -= high.begin()->isLight;
					high_sum -= high.begin()->power;
					high.erase(high.begin());
				}
				else{	//delete lightspell from high
					num_of_lightning_high--;
					high_sum -= power;
					high.erase({isLight, power});
				}
			}
		}//end deletion
		
		if(high.empty() && low.empty())
			result = 0;
		else if(high.empty() && !low.empty())
			result = low_sum;
		else if(!high.empty() && low.empty())	//thanks to corolary 1) they are all lightning
			result = 2*high_sum - high.begin()->power;
		else{	//are both non empty
			if(num_of_lightning_high != k)
				result = low_sum + 2*high_sum; 	//we can double all the best spells
			else
				result = low_sum + 2*high_sum - high.begin()->power + low.rbegin()->power;
				//we have all lightning spell, so the smallest is not doubled, and the 
				//greatest lightning spell can double a firespell
		}

		//print(low, high);
		cout <<result<<endl;
	
	}
    return 0;
}