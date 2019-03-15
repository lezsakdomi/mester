// Feladat: Találkozások
// Lezsák Domonkos

//#include <bits/stdc++.h>
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
#include <queue>
#include <list>
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

int max_priority = 0;
struct Event {
	int time;
	int priority;
	bool be;
	int person;
	Event(int time, bool be, int person) : time(time), priority(!be), be(be), person(person) { cerr<<"> "<<*this<<endl; }
	bool operator<(const Event& o) const { return time>o.time || (time==o.time && priority>o.priority); }
	friend std::ostream& operator<<(ostream& os, const Event& e) { return os<<e.time<<": #"<<e.person<<" "<<(e.be?"BE":"KI"); }
};
priority_queue<Event> events;

class NOTFOUND: public exception {};

int i, j, k, l, m, n, o, p, x, y, z;
vector<int> v;
set<int> bent;

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	cin>>n; v.resize(n);
	fe (i, 0, n) {
		initi(erk);
		initi(tav);
		events.push(Event(erk, true, i));
		events.push(Event(tav, false, i));
	}
	cerr<<"Thanks!"<<endl;

	while(!events.empty()) {
		list<int> frissenjott;
		int t=events.top().time;
		cerr<<"t="<<t<<endl;
		while(!events.empty() && events.top().time==t && events.top().be){
			cerr<<"] "<<events.top()<<endl;
			frissenjott.push_back(events.top().person);
			events.pop();
		}

		for (int p: frissenjott) {
			assert(v[p]==0);
			v[p]=bent.size()+frissenjott.size();
		}
		for (int p: bent) {
			v[p]+=frissenjott.size();
		}
		bent.insert(frissenjott.begin(), frissenjott.end());

		while(!events.empty() && events.top().time==t){
			assert(!events.top().be);
			cerr<<"[ "<<events.top()<<endl;
			bent.erase(events.top().person);
			events.pop();
		}
	}

	auto best=std::max_element(v.begin(), v.end());
	cout<<distance(v.begin(), best)+1<<endl; // ID is zero-based internally
	cout<<*best-1<<endl; // Counting himself everytime

	return 0;
}
