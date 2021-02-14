#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Execution time on codeforces: 
	
	Correctness: algorithm presented in class
		
	Time complexity:
			
	Space complexity:
		
*/

class Frog{
	public:
	int pos;
	int tongue;
	int real_tongue;
	int mosquitoEaten;
	
	Frog(int x, int y){
		pos = x;
		tongue = y;
		real_tongue = y;
		mosquitoEaten = 0;
	}
	
	int end(){
		return pos+tongue;
	}
	
	void set(int x, int y){
		pos = x;
		tongue = y;
	}
	
	void eat(int v){
		tongue += v;
		real_tongue += v;
		++mosquitoEaten;
	}
};

//global variable
vector<Frog> frogs;


void print(map<int, int> map, vector<Frog> &frogs){
	for(auto it = map.begin(); it != map.end(); ++it)
		cout << it->first << "\t" << frogs[it->second].tongue  << endl;
}

int main() {

	int n {};
	int m {};

	//collect frogs
	std::cin >> n;
	std::cin >> m;
	frogs.reserve(n);
	vector<int> sortedFrogs;
	sortedFrogs.reserve(n);
	std::map<int, int> map;
	int x {};
	int y {};
	for (int i {}; i < n; ++i) {
		scanf("%d%d ", &x, &y);
		Frog f = Frog(x, y);
		frogs.push_back(f);
		sortedFrogs.push_back(i);
	}

	sort(sortedFrogs.begin(), sortedFrogs.end(), [](auto& a, auto& b) { return frogs[a].pos < frogs[b].pos; });
    int max_end = -1;
    for(auto f : sortedFrogs){
        if(frogs[f].pos <= max_end) {//it's totally or partially contained
			if(frogs[f].end() <= max_end){
				//this frog is inaccessible, skip
			}
			else{
				int new_pos = max_end+1;
				int new_tongue = frogs[f].tongue - (new_pos - frogs[f].pos);	//new tongue = old tongue - difference of pos
				frogs[f].set(new_pos, new_tongue);
				//insert pair (pos, index) into map
				map.insert({new_pos, f});
				max_end = frogs[f].end();
			}
		}
		else{	//it's outside
			//insert pair (pos, index) into map
			map.insert({frogs[f].pos, f});
            max_end = frogs[f].end();
        }
	}

	
	//normalize data, removing inaccessible frogs and resizing overlapping frogs to
	//eliminate overlapping
	auto prev = map.begin();
	auto curr = next(prev, 1);
	/*while(curr != map.end()){
		int p = prev->second;
		int c = curr->second;
		if(frogs[c].pos <= frogs[p].end()){
			if(frogs[c].end() <= frogs[p].end()){	//curr is inside prev
				map.erase(curr);
				curr = next(prev, 1);
			}
			else{											//curr is paritally inside
				//modify frog inside frogs
				int new_pos = frogs[p].end()+1;
				int new_tongue = frogs[c].tongue - (new_pos - frogs[c].pos);	//new tongue = old tongue - difference of pos
				frogs[c].set(new_pos, new_tongue);
				//insert pair (pos, index) into map
				map.erase(curr);
				curr = (map.insert({new_pos, c})).first; 	//insert returns a <iterator, bool> pair
				//advance
				prev = curr;
				curr++;
			}
		}
		else{
			prev = curr;
			++curr;
		}
	}*/
	
	//cout <<"collected data:"<<endl;
	//print(map, frogs);


	//eat mosquitoes
	int pos;
	int value;
	std::multimap<int, int> uneaten;
	for (int i {}; i < m; ++i) {
		std::cin >> pos;
		std::cin >> value;
		if(pos < map.begin()->first){
			continue;	//if the mosquito is before every frog, can be discarded
		}
		
		 
		auto frog = --map.upper_bound(pos);	//the frog at the left of pos
		int f = frog->second;
		if(pos <= frogs[f].end()){	//mosquito gets eaten
			//eat mosquito
			frogs[f].eat(value);
			
			//eat possible other mosquitoes
			bool eatenAll = false;
			while(!eatenAll){
				auto mosquito = uneaten.lower_bound(frogs[f].pos);
				if(mosquito != uneaten.end() && mosquito->first <= frogs[f].end()){
					frogs[f].eat(mosquito->second);
					uneaten.erase(mosquito);
				}
				else
					eatenAll = true;
			}
			
			//normalize frog map
			bool normalized = false;
			while(!normalized){
				auto nextFrog = next(frog, 1);
				if(nextFrog == map.end())	//frog is the last frog, so the map is normalized
					break;
				int n = nextFrog->second;
				if(frogs[n].pos <= frogs[f].end()){
					if(frogs[n].end() <= frogs[f].end()){	//next is inside frog
						map.erase(nextFrog);
					}
					else{											//nextFrog is paritally inside
						//modify frog inside frogs
						int new_pos = frogs[f].end()+1;
						int new_tongue = frogs[n].tongue - (new_pos - frogs[n].pos);	//new tongue = old tongue - difference of pos
						frogs[n].set(new_pos, new_tongue);
						//insert pair (pos, index) into map
						map.erase(nextFrog);
						map.insert({new_pos, n});
						normalized = true;
					}
				}
				else
					normalized = true;
			}
		}
		else{	//mosquito is stored in uneatenMosquito set
			uneaten.insert({pos, value});
		}
		//cout << "inserted: " << pos <<","<<value<<endl;
		//print(map, frogs);
	}
		
		
	for(Frog f : frogs)
		cout << f.mosquitoEaten << " "<< f.real_tongue<< endl;
	
	/*
		5 3
		3 2
		2 4	
		10 5
		9 2
		14 1
		8 1
		8 2
		5 2
	*/
	
    return 0;
}