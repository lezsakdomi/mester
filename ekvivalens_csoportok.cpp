// Feladat: Haladó / Sorozatok / Ekvivalens csoportok * 
// Lezsák Domonkos
// TODO add_compile_options(-std=c++11 -DDEBUG)

//#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <numeric>
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

class NOTFOUND: public exception {};

int i, j, k, l, m, n, o, p, x, y, z;
vector<vector<bool>> v(30, vector<bool>(10000, false));
vector<bool> was(10000, false);

bool iseq(int a, int b){
    if (!was[a] || !was[b]) return true;
    fv(i, v) if (v[i][a] != v[i][b]) return false;
    return true;
}

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n;
    fe (i, 0, n) {
        int c; cin>>c; c--;
        while(1){
            int i; cin>>i;
            if (!i) break;
            i--;
            v[c][i]=true;
            was[i]=true;
            //cerr<<c<<":"<<i<<endl;
        }
    }
    cerr<<"Thanks!"<<endl;

    fv(c, v) {
        fe(i, 0, 80) cerr<<(v[c][i] ? '#' : '|');
        cerr<<endl;
    }

    cerr<<endl;

    vector<vector<int>> vv(0);

    fe(i, 0, 10000) {
        if (!was.at(i)) continue;
        bool hit = false;
        for (auto&& it : vv) {
            if (iseq(it.front(), i)) {
                cerr<<"iseq("<<it.front()<<", "<<i<<")"<<endl;
                it.push_back(i);
                hit = true;
                break;
            }
        }
        if (!hit) vv.push_back(vector<int>(1, i));
    }

    cout<<vv.size()<<endl;
    for(auto it : vv) {
        for (auto iit : it) cout<<iit+1<<" ";
        cout<<endl;
    }

    return 0;
}
