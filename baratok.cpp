// Feladat: Haladó / Sorozatok / Barátok *** 
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

struct Node {
    string name;
    Node* child;
    vector<Node*> parents;
    Node(string name): name(name) {}
    void setChild(Node* child){
        assert(this->child==0);
        this->child=child;
        this->child->parents.push_back(this);
    }
    bool marked=false;
    bool marked2=false;
    bool marked3=false;
};

int i, j, k, l, m, n, o, p, x, y, z;
vector<pair<string, string>> input;
map<string, Node*> v;

void eb(Node* n){
    if (n->marked2) return;
    n->marked2=true;
    n->marked3=true;
    if(n->child) eb(n->child);
}

void hb(Node* n){
    if (n->marked3) return;
    n->marked3=true;
    for (auto n_:n->parents) hb(n_);
    if (n->parents.size()==0) eb(n);
}

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n; input.resize(n);
    cin.get();
    if(cin.peek()=='\n')cin.get();
    fe (i, 0, n) {
        cerr<<"[";
        while(!cin.eof()) {
            char c; cin.get(c);
            if (c==' ') break;
            else input[i].first+=c;
            cerr<<c;
        }
        cerr<<"] -> [";
        while(!cin.eof()) {
            char c; cin.get(c);
            if (c=='\n' || c=='\r') break;
            else input[i].second+=c;
            cerr<<c;
        }
        if(cin.peek()=='\n')cin.get();
        cerr<<"]"<<endl;
    }
    cerr<<"Thanks!"<<endl;

    for(auto it:input) v[it.first]=new Node(it.first);
    for(auto it:input) v[it.first]->setChild(v[it.second]);

    cerr<<"---debug---"<<endl;
    for (auto it : v) {
        cerr<<it.first<<": ";
        for (auto it : it.second->parents) cerr<<"["<<it->name<<"] ";
        cerr<<endl;
    }
    cerr<<"..........."<<endl;

    {
        vector<string>w;
        for(auto n:v)if(n.second->parents.size()==0)w.push_back(n.second->name);
        if(w.size()) {for (auto it:w)cout<<it<<" ";cout<<endl;}
        else cout<<"-"<<endl;
    }

    {
        vector<pair<string, string>> w;
        for (auto it:v) {
            auto const n=it.second;
            if(n->marked) continue; 
            if (n->parents.size() == 1 && n->parents[0] == n->child && n->child->parents.size() == 1 && n->child->parents[0] == n) {
                n->marked=true;
                n->child->marked=true;
                w.push_back({n->name, n->child->name});
            }
        }
        if(w.size()) {for (auto it:w)cout<<it.first<<"-"<<it.second<<" ";cout<<endl;}
        else cout<<"-"<<endl;
    }

    {
        int maxb=0;
        for (auto it:v) maxb=max(maxb, (int)it.second->parents.size());
        for (auto it:v) if((int)it.second->parents.size()==maxb) cout<<it.second->name<<" "; cout<<endl;
    }

    if (true) {
        int cnt=0;
        for (auto it:v) {
            auto const n=it.second;
            if(n->marked3 || n->marked2) continue; 
            hb(n);
            cnt++;
        }
        cout<<cnt<<endl;
    } else cout<<2<<endl;

    return 0;
}
