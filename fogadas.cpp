// Feladat: Haladó / Sorozatok / Fogadás ** 
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
vector<vector<bool>> v;

pair<bool, vector<int>> bt(int cnode, vector<int> history, set<int> was) {
    history.push_back(cnode);
    was.insert(cnode);

    if ((int)history.size() == n) return {true, history};

    fe (i, 0, n) { if (!v[cnode][i]) continue; auto nnode = i;
        if (was.find(nnode)!=was.end()) continue;
        auto r = bt(nnode, history, was);
        if (r.first) return r;
    }

    return {false, history};
}

// === MAIN ===
int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n; v.resize(n, vector<bool>(n, false));
    cin>>m;
    fe (i, 0, m) {
        cin>>x>>y; x--; y--;
        v[x][y] = v[y][x] = true;
    }
    cerr<<"Thanks!"<<endl;

    fv(i, v) {
        fv(j, v[i]) {
            cerr<<(v[i][j]?"#":"+");
        }
        cerr<<endl;
    }
    cerr<<endl;

    // Elso vendeg megkeresese
    int front;
    for (front = 0; ; front++){
        vector<bool> v_ = v[front];
        fe(i, 0, n) fe(j, 0, n) {
            if (!v[i][front]) break;
            fe(j, 0, n) v_[j] = v_[j] && v[i][front];
        }
        if (v_ == v[front]) break;
    }

    vector<int> vv;
    vv.push_back(front);

    // Tovabbi sorrendek meghatarozasa
    int localBack = front; // Feltetelezett utolso elem
    fe(i, 1, n) {
        vector<bool> vv_ = v[localBack]; // v[localBack]\vv == vv..localBack
        fv(i, vv) {vv_[vv[i]]=false;}
        int min = n + 1;
        fe(i, 0, n) {
            if (!vv_[i]) continue;
            // | v[i]\vv |
            // TODO
        }
    }
    
    // Trash

    auto r = bt(front, vector<int>(), set<int>());
    if (r.first) {
        for (auto it : r.second) cout<<it+1<<" ";
        return 0;
    }

    return 1;
}
