// Feladat: Haladó / Gráfok, elemi feladatok / Ismerősök * 
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
vector<long long unsigned int> v, w;

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n>>m; v.resize(n, 0); w.resize(n, 0);
    fe (i, 0, m) {
        cin>>x>>y; x--; y--;
        v[x]=v[x]|((long long unsigned int)1<<y);
        v[y]=v[y]|((long long unsigned int)1<<x);
        w[x]++; w[y]++;
    }
    cerr<<"Thanks!"<<endl;

    fe (i, 0, n) {
        cerr<<w[i]<<' ';
        fe (j, 0, n) {
            if (v[i] & ((long long unsigned int)1<<j)) {
                cerr<<'#';
            } else {
                cerr<<' ';
            }
        }
        cerr<<endl;
    }
    cerr<<endl;

    {
        vector<pair<int, int>> vv;
        fe (i, 0, n) fe (j, i+1, n) {
            const long long unsigned a=v[i]^((long long unsigned int)1<<j);
            const long long unsigned b=v[j]^((long long unsigned int)1<<i);
            if ((a==b) && (a>0)) vv.push_back({i, j});
        }
        for(auto&& it : vv) { if (it.first>it.second) std::swap(it.first, it.second); }
        std::sort(vv.begin(), vv.end(), [](pair<int, int> a, pair<int, int> b){ return to_string(a.first)+to_string(a.second) < to_string(b.first)+to_string(b.second); });
        cout<<vv.size()<<endl;
        fv(i, vv) {
            cout<<vv[i].first+1<<" "<<vv[i].second+1<<endl;
        }
    }

    {
        vector<pair<int, int>> vv;
        fe (i, 0, n) fe (j, i+1, n) {
            if (v[i] & v[j]) vv.push_back({i, j});
        }
        for(auto&& it : vv) { if (it.first>it.second) std::swap(it.first, it.second); }
        std::sort(vv.begin(), vv.end(), [](pair<int, int> a, pair<int, int> b){ return to_string(a.first)+to_string(a.second) < to_string(b.first)+to_string(b.second); });
        cout<<vv.size()<<endl;
        fv(i, vv) {
            cout<<vv[i].first+1<<" "<<vv[i].second+1<<endl;
        }
    }

    return 0;
}
