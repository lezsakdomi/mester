// Feladat: OKTV 2017-18 3. ford. - 1. Csatornák
// Lezsák DOmonkos
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

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--; b--;
    
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>(0)); // {sz, id}
    for (int i=0; i<n; i++) {
        int x, y, sz;
        cin >> x >> y >> sz;
        x--; y--;

        g[x].push_back({sz, y});
        
    }
}
