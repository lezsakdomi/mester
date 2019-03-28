// Feladat: Haladó / Gráfok, legrövidebb utak / Repülőút *** 
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
#include <cstdio>
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

struct V {
    int hova;
    int mikor;
    int ido;
    int id;
};

int i, j, k, l, m, n, o, p, x, y, z, a, b, c;
vector<vector<V>> v;
vector<V> jaratok;

static int NAP = 24*60;

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n>>m>>a>>b; a--; b--;
    v.resize(n); jaratok.resize(m);
    fe (i, 0, m) {
	int zs;
        cin>>x>>y>>z>>zs; x--; y--;
        v[x].push_back(jaratok[i] = {y, z, zs, i});
        // hova, mikor, mennyi idő
    }
    cerr<<"Thanks!"<<endl;

    vector<bool> touched(n);

    // mikorra, útvonal
    priority_queue<
        pair<int, vector<int>>,
        vector<pair<int, vector<int>>>,
        function<bool(pair<int, vector<int>>, pair<int, vector<int>>)>
            > q(
                    [](pair<int, vector<int>> a, pair<int, vector<int>> b){return a.first>b.first;},
                    vector<pair<int, vector<int>>>(0)
                    );
    fv(j, v[a]) {
        q.push({v[a][j].mikor+v[a][j].ido+60, vector<int>(1, v[a][j].id)});
    }
    touched[a]=true;
    while(!q.empty()){
        //if (q.top().second.back()==b) break;
        auto top = q.top();
        vector<int> ut = top.second;
        V utolsoJarat = jaratok[ut.back()];
        int most = utolsoJarat.hova;
        int ido = top.first;
        fprintf(stderr, "> at %d on %d with %d\n", ido, most+1, utolsoJarat.id+1);
        if (most==b) {
            fprintf(stderr, "DONE\n");
            break;
        }
        q.pop();
        if (touched[most]) {
            fprintf(stderr, "SEEN\n");
            continue;
        }
        touched[most]=true;
        fv(j, v[most]) {
            int hova = v[most][j].hova;
            int jaratIndulas = v[most][j].mikor;
            int hossz = v[most][j].ido;
            int jaratId = v[most][j].id;
            vector<int> v_=ut;

            //            nap       éjszakázunk?                                    járat indulása napon belül
            int indulas = ido/NAP + (jaratIndulas </*TODO =?*/ ido%NAP ? NAP : 0) + jaratIndulas;
            int erkezes = indulas + hossz + 60;
            v_.push_back(jaratId);

            fprintf(stderr, ">>> to %d at %d-%d with %d\n", hova+1, indulas, erkezes, jaratId+1);

            if (touched[hova]) {
                fprintf(stderr, "    SEEN\n");
                continue;
            }

            q.push({erkezes, v_});
        }
    }

    if (q.empty()) cout<<0<<endl;
    else {
        auto top = q.top();
        vector<int> ut = top.second;
        V utolsoJarat = jaratok[ut.back()];
        int most = utolsoJarat.hova;
        int ido = top.first;

        cout<<ido-60<<endl;
        cout<<ut.size()<<" ";
        fv(j, ut) cout<<ut[j]+1<<" "; cout<<endl;
    }

    return 0;
}
