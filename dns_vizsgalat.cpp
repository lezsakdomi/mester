// Feladat: DNS vizsgálat
// Lezsák Domonkos
// TODO add_compile_options(-std=c++11 -DDEBUG)

#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <limits>
#include <vector>
#include <map>
#include <set>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id
#define initi(id) int id; cin>>id
#define fe(id, from, to) for (int id=from; id<to; id++)
#define f(id, from, to) for (int id=from; id<to; id++)
#define fh(id, to, from) for (int id=from-1; id>=to; id--)
#define fv(id, v) for (int id=0; id<(int)v.size(); id++)

typedef int dp_key;
const int MINDPKEY=0;
const int MAXDPKEY=numeric_limits<dp_key>::max();
typedef int dp_return;
map<dp_key, dp_return> dp_cache;
dp_return calc_dp(dp_key key, set<dp_key> call_stack);
dp_return dp(dp_key key, set<dp_key> call_stack = set<dp_key>()) {
	if (key < MINDPKEY) throw invalid_argument("i<0");
	if (key > MAXDPKEY) throw invalid_argument("i>0");
	if (!call_stack.insert(key).second) throw logic_error("Infinite recursion!");

	map<dp_key, dp_return>::iterator it = dp_cache.find(key);
	if (it != dp_cache.end()) return it->second;
	else {
		dp_return result = calc_dp(key, call_stack);
		dp_cache[key] = result;
		return result;
	}
}
dp_return calc_dp(dp_key key, set<dp_key> call_stack){
	(void)key;
	(void)call_stack;
	return 0;
}

int max_priority = 0;
struct Event {
	int time;
	int priority;
	Event(int time) : time(time), priority(max_priority++) { cerr<<"> "<<*this<<endl; }
	bool operator<(const Event& o) const { return time>o.time || (time==o.time && priority>o.priority); }
	friend std::ostream& operator<<(ostream& os, const Event& e) { return os<<e.time<<": "; }
};
priority_queue<Event> events;

int i, j, k, l, m, n, o, p, x, y, z;
vector<int> v;
int last[4]={-1, -1, -1, -1};
const char* ls="ACGT";

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	v.reserve(20000);
	while(cin.peek()!='\n') {
		init(char, c);
		fe(i,0,5){
			if (ls[i]) {
				if (ls[i]==c) {
					v.push_back(i);
					cerr<<"\033[32m"<<c<<"\033[0m";
					break;
				}
			} else throw runtime_error("bad letter");
		}

	}
	cerr<<endl;
	cerr<<"Thanks!"<<endl;

	k=-1;
	fv(i, v) {
		fe(j,0,4) {
			if (last[j]<i) {
				try {
					cerr<<"\033[33m"<<ls[j]<<": ";
					while(v.at(++last[j])!=j) cerr<<ls[v[last[j]]];
					cerr<<"\033[32m"<<ls[v[last[j]]];
				} catch (...) {
					cerr<<"\033[31m|";
				}
				cerr<<"\033[0m"<<endl;
			}
		}
		int mi=*last, ma=*last;
		fe(j,0,4)mi=min(mi, last[j]);
		fe(j,0,4)ma=max(ma, last[j]);
		k=max(k, ma-mi);
		fe(i,0,4) {
			cerr<<"\033[34m] "<<ls[i]<<": "<<last[i]<<(last[i]==ma?" *":"")<<"\033[0m"<<endl;
		}
		cerr<<i<<" "<<ls[v[i]]<<": "<<mi<<"-"<<ma<<" "<<k<<endl;
		assert(mi==i);
		assert(mi>=0);
	}

	cout<<k+1<<endl;

	return 0;
}
