// Feladat: Szókereső
// Lezsák Domonkos

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
vector<vector<char>> v;

class NOTFOUND: public exception {};
class CIRCULAR: public NOTFOUND {};

#define valid(i2, j2) (!((i2)<0 || (j2)<0 || (i2)>=n || (j2)>=n))

struct SR {
	int i, j;
	string path;
	int oi, oj;
	SR(int i, int j, string path=""): i(i), j(j), path(path), oi(i), oj(j) {
		assert(valid(i, j));
	}
	char diff(const SR& res) const {
		assert(valid(i, j));
		if (this->i!=res.i) {
			assert(this->j==res.j);
			switch (res.i-this->i) {
				case 1: return 'F';
				case -1: return 'L';
			}
		} else if (this->j!=res.j) {
			assert(this->i==res.i);
			switch (res.j-this->j) {
				case 1: return 'B';
				case -1: return 'J';
			}
		}
		throw std::runtime_error("Invalid step");
	}
	SR bto(int i, int j) {
		assert(valid(i, j));
		SR res(i, j);
		res.path=diff(res)+path;
		res.oi=this->oi; res.oj=this->oj;
		return res;
	}
};

#define test(i2, j2) { \
	if valid((i2), (j2)) try { \
		return solve((i2), (j2), s, r+1, used).bto(i, j); \
	} catch (NOTFOUND) {} \
} void()

SR solve(int i, int j, string s, size_t r = 0, set<pair<int, int>> used = set<pair<int, int>>()) {
	if (used.find({i, j})!=used.end()) throw CIRCULAR();
	else used.insert({i, j});
	assert(valid(i, j));
	if (v.at(i).at(j)!=s.at(r)) throw NOTFOUND();
	assert(s.size() > 0);
	if (r == s.size()-1) return SR(i, j);
	test(i+1, j);
	test(i-1, j);
	test(i, j+1);
	test(i, j-1);
	throw NOTFOUND();
}

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	cin>>n; v.resize(n, vector<char>(n));
	fe (i, 0, n) {
		fe(j, 0, n) {
			cin>>v.at(i).at(j);
		}
		{string s; getline(cin, s); assert(s.size()==0);}
	}
	string s; getline(cin, s); assert(s.size()>0);
	cerr<<"Thanks!"<<endl;
	
	fe (i, 0, n) fe (j, 0, n) {
		try {
			SR res = solve(i, j, s);
			assert(res.path.size()==s.size()-1);
			cout<<i+1<<" "<<j+1;
			cerr<<"..";
			cerr<<res.oi+1<<" "<<res.oj+1;
			cout<<endl;
			cout<<res.path<<endl;
#ifndef DEBUG
			return 0;
#endif
		} catch (NOTFOUND) {}
	}

#ifndef DEBUG
	cout<<"0 0"<<endl;
#endif

	return 0;
}
