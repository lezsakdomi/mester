// Feladat: Középhaladó / Közismereti emeltszintű érettségi feladatok / Telefonos ügyfélszolgálat - 2016. október 
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
#include <deque>
#include <stack>
#include <functional>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id
#define initi(id) int id; cin>>id
#define fe(id, from, to) for (int id=from; id<to; id++)
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
vector<pair<int, int>> v;

void fel(int i, function<void()> f){
#ifdef DEBUG
    cerr<<i<<". feladat ";
#endif
    cout<<"#"<<endl;
    f();
}

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n; v.resize(n);
    cin>>x>>y>>z;
    a=x*3600+y*60+z;
    fe (i, 0, n) {
        cin>>x>>y>>z;
        v[i].first = x*3600+y*60+z;
        cin>>x>>y>>z;
        v[i].second = x*3600+y*60+z;
    }
    std::sort(v.begin(), v.end());
    cerr<<"Thanks!"<<endl;

    v.push_back({0, 0});

    fel(1, [&](){
        vector<pair<int, int>> vv;
        for(int i=0, j=0; i<24; i++){
            int cnt=0;
            while(v[j].first<i*3600)j++;
            cnt=-j;
            while(v[j].first<(i+1)*3600)j++;
            cnt+=j;
            if(cnt>0)vv.push_back({i, cnt});
        }
        fv(i, vv)cout<<vv[i].first<<" "<<vv[i].second<<endl;
    });

    fel(2, [&](){
        int mi=0;
        fe(i, 0, n)if(v[mi].second-v[mi].first<v[i].second-v[i].first)mi=i;
        cout<<mi+1<<" "<<v[mi].second-v[mi].first<<endl;
    });

    fel(3, [&](){
        vector<int> vv;
        vector<pair<int, int>> const* v_ = &v;
        fe(i, 0, n) if (v[i].first<= a && a<=v[i].second) vv.push_back(i);
        //sort(vv.begin(), vv.end(), [v_](int a, int b){return v_->at(a).second < v_->at(b).second;});
        //for(auto it : vv)cerr<<it<<" "; cerr<<endl;
        if (vv.empty()) cout<<"Nem"<<endl;
        else cout<<vv.front()+1<<" "<<vv.size()-1<<endl;
    });

    fel(4, [&](){
        int mi=-1;
        fe(i, 0, n){
            if(v[i].first<12*3600)mi=i;
        }
        if (mi==-1) cout<<"Nem"<<endl;
        else {
            int mj=n;
            fe(j,0,n){
                if (mi==j) continue;
                if (v[j].first>v[mi].first) continue;
                if (v[j].second>v[mj].second) mj=j;
            }
            cout<<mi+1<<" "<<max(0, max(v[mj].second, 8*3600)-v[mi].first)<<endl;
        }
    });

    fel(5, [&](){
        int elveg=8*3600;
        fe(i, 0, n){
            if (v[i].first>=12*3600) break;
            if (v[i].second<8*3600) continue;
            elveg=max(elveg, v[i].first);
            if (i!=0) {
                elveg=max(elveg, v[i-1].second);
            }
            if (elveg>=v[i].second) continue;
            cout<<i+1<<" ";
            cout<<elveg/3600<<" "<<elveg/60%60<<" "<<elveg%60<<" ";
            cout<<v[i].second/3600<<" "<<v[i].second/60%60<<" "<<v[i].second%60<<" ";
            cout<<endl;
        }
    });

    return 0;
}
