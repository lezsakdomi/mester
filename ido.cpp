// Feladat: Kezdő / Elemi feladatok / Idő * 
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
#include <iomanip>
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

int io, ip, imp, iszmp, d_o, dp, dmp, dszmp, po, pp, pmp, pszmp, mo, mp, mmp, mszmp;
vector<int> v;

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>io>>ip>>imp>>iszmp>>d_o>>dp>>dmp>>dszmp;
    cerr<<"Thanks!"<<endl;

    po=io-d_o;
    pp=ip-dp;
    pmp=imp-dmp;
    pszmp=iszmp-dszmp;

    pmp+=pszmp/100; pszmp%=100;
    pp+=pmp/60; pmp%=60;
    po+=pp/60; pp%=60;
    po%=24;

    cout<<po<<" "<<pp<<" "<<pmp<<" "<<pszmp<<" "<<endl;
    cout<<"0 0 0 0"<<endl;

    return 0;
}
