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

class NOTFOUND: public exception {};

class throw_output_iterator: public std::iterator<std::output_iterator_tag, throw_output_iterator> {
    protected:
        size_t position = 0;

    public:
        template<typename T>
        void operator=(T const& value) {
            throw std::make_tuple(*this, value, position);
        }

        throw_output_iterator& operator++() {
            this->position++;
            return *this;
        }

        const throw_output_iterator& operator*() const {
            return *this;
        }

        throw_output_iterator& operator*() {
            return *this;
        }
};

bool operator<(pair<int, int> a, pair<int, int> b) {
    return (a.first < b.first) || (a.second < b.second);
}

/*
MyIt mysetop(Op op, MyIt it1, MyIt it2) {
    MyIt result;
    op(it1, myItEnd, it2, myItEnd, result);
    return result;
}
*/

int i, j, k, l, m, n, o, p, x, y, z;
vector<set<int>> v;

int main(){
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
#endif
    cin>>n>>m; v.resize(n);
    fe (i, 0, m) {
        cin>>x>>y; x--; y--;
        v[x].insert(y);
        v[y].insert(x);
    }
    cerr<<"Thanks!"<<endl;

    {
        vector<pair<int, int>> vv;
        fe(i, 0, n) fe(j, i+1, n) {
            if (v[i].empty()) continue;
            //if (v[i].size() != v[j].size()) continue;
            //bool ok = true;
            //for (auto iti=v[i].begin(), itj=v[j].begin(); iti!=v[i].end() && itj!=v[j].end(); iti++, itj++) {
            //    if (*iti != *itj) {
            //        ok = false;
            //        break;
            //    }
            //}
            try {
                const std::vector<int> set_i = {i}, set_j = {j};
                std::vector<int> a, b;
                std::set_difference(v[i].begin(), v[i].end(), set_j.begin(), set_j.end(), std::back_inserter(a));
                std::set_difference(v[j].begin(), v[j].end(), set_i.begin(), set_i.end(), std::back_inserter(b));
                if (!a.size()) continue;
                std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), throw_output_iterator());
                vv.push_back({i, j});
            } catch (std::tuple<throw_output_iterator, int, size_t>) { continue; }
            //if (!ok) vv.insert({i, j});
        }
        cout<<vv.size()<<endl;
        for(auto it : vv) cout<<it.first+1<<" "<<it.second+1<<endl;
    }
    {
        vector<pair<int, int>> vv;
        fe(i, 0, n) fe(j, i+1, n) {
            //if (std::set_intersection(v[i].begin(), v[i].end(), v[j].begin(), v[j].end(), throw_output_iterator()).empty()) vv.insert({i, j});
            try {
                std::set_intersection(v[i].begin(), v[i].end(), v[j].begin(), v[j].end(), throw_output_iterator());
            } catch (std::tuple<throw_output_iterator, int, size_t>) {
                vv.push_back({i, j});
            }
        }
        cout<<vv.size()<<endl;
        for(auto it : vv) cout<<it.first+1<<" "<<it.second+1<<endl;
    }
    return 0;
}
