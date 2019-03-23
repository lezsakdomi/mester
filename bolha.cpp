// Feladat: Haladó / Gráfok, szélességi bejárás / Bolha ** 
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
#define f(id, from, to) for (int id=from; id<to; id++)
#define fh(id, to, from) for (int id=from-1; id>=to; id--)
#define fv(id, v) for (int id=0; id<(int)v.size(); id++)

int i, j, k, l, m, n, o, p, x, y, z, a, b, c;
vector<pair<int, pair<int, int>>> v;

int nextk(int k) {
    return k/2*2+(1-k%2);
}

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n>>m; v.resize(n);
    fe (i, 0, n) {
        cin>>x;
        v[i].first = x;
        v[i].second.first=numeric_limits<int>::max();
    }
    fe (i, 0, m) {
        cin>>x>>y>>z; x--; y--;
        if (z<v[x].second.first) v[x].second={z, y};
        if (z<v[y].second.first) v[y].second={z, x};
    }
    cerr<<"Thanks!"<<endl;

    fe(i, 0, n) assert(v[i].second.first!=numeric_limits<int>::max());
    fe(i, 0, n) v[i].second.first=-1;

    function<int(int, int, int)> mb = [&](int i, int k, int l = 0){
        cerr<<std::string(l, ' ')<<"] ("<<i<<", "<<k<<")"<<endl;
        if (v[i].second.first<0) {
            v[i].second.first = k;
            cerr<<std::string(l, ' ')<<"> ("<<i<<", "<<v[i].second.first<<")"<<endl;
            v[i].second.first = mb(v[i].second.second, nextk(k), l+1);
            cerr<<std::string(l, ' ')<<"< ("<<i<<", "<<v[i].second.first<<")"<<endl;
        } else {
            cerr<<std::string(l, ' ')<<"[ ("<<i<<", "<<v[i].second.first<<")"<<endl;
        }
        return nextk(v[i].second.first);
    };

    int k=0; fe(i, 0, n) k=max(k, mb(i, k, 0)/2*2)+2;

#ifdef DEBUG
    //fe(i, 0, 10) cerr<<i<<">"<<nextk(i)<<" "; cerr<<endl;
    fe(i, 0, n) cerr<<i%10<<" "; cerr<<endl;
#endif

#ifdef DEBUG
    fe(i, 0, n) cerr<<v[i].second.first<<" "; cerr<<endl;
#endif
    
    cerr<<"Done"<<endl;

    vector<int> vv(k+1, 0);
    fe(i, 0, n) vv.at(v[i].second.first)+=v[i].first;

    int mi=0;
    fe(i, 0, k+1){
        if (vv[mi]<vv[i]) mi=i;
    }
    cout<<vv[mi]<<endl;
    cerr<<"At: "<<mi<<endl;

    return 0;
}
