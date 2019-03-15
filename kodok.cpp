// Feladat: NT, OKTV, IOI Válogató / IOI Válogató 2017 / Kódok 
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

int i, j, k, l, m, n, o, p, x, y, z, a, b, c;
vector<vector<bool>> v;

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n; v.resize(n);
    fe (i, 0, n) {
        string s; cin>>s;
        v[i].resize(s.size());
        fe(j, 0, (int)s.size()) {
            v[i][j]=s[j]=='1';
        }
    }
    cerr<<"Thanks!"<<endl;

    vector<vector<int>> w(n, vector<int>(0));
    fe(i, 0, n) {
        vector<bool>& v_ = v[i];
        vector<int>& w_ = w[i];

        for(int j=0; j<(int)v_.size(); j+=3) {
            cerr<<" "<<j<<endl;
            // X 000 -> 011
            // 0 000 -> 110
            // 0 001 -> 010
            // 1 001
            // X 010
            // 0 011 -> 101
            // 1 011
            if (v_[j] != v_[j+1] && v_[j+1] != v_[j+2]) continue;

            bool prev = j ? v_[j-1] : !v_[j];

            if (prev != v_[j] && v_[j] != v_[j+2]) continue;

            cerr<<"  flip"<<endl;
            //cerr<<"   "; fe(k, 0, (int)w_.size()) cerr<<w_[k]<<" "; cerr<<endl;
            
            if (v_[j] == v_[j+1] && v_[j+1] == v_[j+2]) {
                cerr<<"   3eq"<<endl;
                if (v_[j] == prev) {
                    w_.push_back(j);
                    v_[j+0] = !v_[j+0];
                    v_[j+1] = !v_[j+1];
                } else {
                    w_.push_back(j+1);
                    v_[j+1] = !v_[j+1];
                    v_[j+2] = !v_[j+2];
                }
            } else {
                cerr<<"   2eq"<<endl;
                if (v_[j+1] == v_[j+2]) {
                    w_.push_back(j);
                    v_[j+0] = !v_[j+0];
                    v_[j+1] = !v_[j+1];
                } else {
                    w_.push_back(j+1);
                    v_[j+1] = !v_[j+1];
                    v_[j+2] = !v_[j+2];
                }
            }
        }

        cout<<w_.size()<<endl;
        if (w_.size()>0) {
            fe(j, 0, (int)w_.size()) cout<<w_[j]+1<<" "; cout<<endl;
        }
    }

    return 0;
}
