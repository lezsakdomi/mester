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

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#endif
    int m, n; cin>>n>>m;
    //return m/256;
    vector<pair<int, vector<int>>> v(n, {0, vector<int>(2*(n-1))});
    fe (i, 0, m) {
        int x, y; cin>>x>>y; x--; y--;
        v[x].second.at(v[x].first++)=y; v[y].second.at(v[y].first++)=x;
    }
    cerr<<"Thanks!"<<endl;

    vector<int> q(n);
    int *front = &q[0], *back = &q[0];
    *front = -1;
    fe (i, 0, n) if (v[i].first % 2 == 1) {*front = i; break;}
    //*front = 0;
    
    if (*front == -1) return 1;
    assert(0 <= *front && *front <= n);
    
    vector<bool> was(n, false);
    was[*front] = true;
    while (front <= back) {
        fe (i, 0, v[*front].first) if (!was[v[*front].second[i]]) {
            *(++back) = v[*front].second[i];
            was[v[*front].second[i]] = true;
        }
        cout<<(*front)+1<<" ";
        front++;
    }

    return 0;
}
