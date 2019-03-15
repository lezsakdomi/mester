// Feladat: NT, OKTV, IOI Válogató / IOI Válogató 2017 / Vasutak 
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

struct Aj { // Ajánlat
    int to; int ar; // hova, ár
    bool operator<(const Aj& o) const {
        return ar>o.ar;
    }
};

struct Aj_ {
    int to; int ar;
    int from;
    bool operator<(const Aj_& o) const {
        return ar>o.ar;
    }
};

int i, j, k, l, m, n, o, p, x, y, z, a, b, c;
vector<vector<Aj>> v; // szomszédsági lista

vector<vector<int>> v_; // csúcsmátrix

vector<bool> reachable; // Kiépült-e már oda vasútvonal?
vector<pair<int, int>> w; // megoldások
int sum=0; // Eddigi összes elköltött $
void build(int a, int b) { // Utvonal építése a és b között; side-effect a fentebbi változókon
    assert(reachable[a] || reachable[b]);
    assert(v_[a][b] != numeric_limits<int>::max());

    w.push_back({a, b});
    sum+=v_[a][b];

    reachable[a] = reachable[b] = true;
    v_[a][b] = v_[b][a] = numeric_limits<int>::max();
}

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n>>k>>a>>b>>m; a--; b--;
    assert(n>0);
    v.resize(n); v_.resize(n, vector<int>(n, numeric_limits<int>::max())); reachable.resize(n, false);
    fe (i, 0, m) {
        cin>>x; x--;
        cin>>y; y--;
        cin>>z;

        v[x].push_back({y, z});
        v[y].push_back({x, z});

        v_[x][y] = v_[y][x] = min(v_[x][y], z);
    }

    reachable[a]=true;
    cerr<<"Thanks!"<<endl;

    // Dijkstra a és b között
    vector<bool> was(n, 0);
    vector<Aj_*> sol(n, 0);
    std::priority_queue<Aj_> q;
    q.push(Aj_{a, 0, -1});
    while(!q.empty()) {
        Aj_ aj = q.top();
        sol[aj.to]=new Aj_(aj);
        if (aj.to == b) break;
        q.pop();
        fe(i, 0, (int)v[aj.to].size()) {
            if (was[v[aj.to][i].to]) continue;
            q.push({v[aj.to][i].to, aj.ar+v[aj.to][i].ar, aj.to});
            was[v[aj.to][i].to] = 1;
        }
    }
    assert(sol[b]);
    vector<int> rpath(1, b);
    while(rpath.back()!=a) {
        assert(sol[rpath.back()]);
        rpath.push_back(sol[rpath.back()]->from);
    }
    fh(i, 1, rpath.size()) build(rpath[i], rpath[i-1]);
    cerr<<"Dijkstra done."<<endl;

    vector<priority_queue<Aj>> vv(n); // szomszédsági lista; minden árajánlat csak egyszer szerepel
    fe(i, 0, n) {
        fe(j, i, n) {
            if (v_[i][j]!=numeric_limits<int>::max()) {
                vv[i].push({j, v_[i][j]});
            }
        }
    }
    cerr<<"Recalc done"<<endl;

    // Maradék útvonalak építése
    while((int)w.size()<k) {
        int mi = 0; // minimim index
        fe(i, 0, n) {
            if (!reachable[i]) continue;
            if (vv[i].empty()) continue;

            while (reachable[vv[mi].top().to]) vv[mi].pop(); // Kis clean-up :)

            if (vv[i].top().ar<vv[mi].top().ar) mi=i;
        }

        build(mi, vv[mi].top().to);
        vv[mi].pop();
    }
    cerr<<"K reached."<<endl;

    cout<<sum<<endl;
    cout<<w.size()<<endl;
    fe(i, 0, (int)w.size()) {
        cout<<w[i].first+1<<" "<<w[i].second+1<<endl;
    }

    return 0;
}
