// Feladat: Cső vásárlás
// Lezsák Domonkos

//#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <limits>
#include <vector>
#include <map>
#include <set>
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

struct Uzlet {
	int hossz;
	int ar;
	int id;
	bool operator<(Uzlet o) const {
		return (float)hossz/ar<(float)o.hossz/o.ar;
	}
};

struct Uzlet2 {
	int hossz;
	int ar;
	int id;
	Uzlet2(Uzlet uzlet): hossz(uzlet.hossz), ar(uzlet.ar), id(uzlet.id) {}
	bool operator<(Uzlet2 o) const {
		return id<o.id;
	}
};

int i, j, k, l, m, n, o, p, x, y, z;
vector<Uzlet> v;

map<Uzlet2, int> lefed(int m, int l=1, int ma=n) {
	cerr<<"\033[33m"; fe(i,0,l) cerr<<">"; cerr<<" "<<m<<"\033[0m"<<endl;
	if (m==0) return map<Uzlet2, int>();
	if (m<0) throw NOTFOUND();
	fe(i, 0, ma) {
		cerr<<"\033[0m"; fe(i,0,l) cerr<<">"; cerr<<" "<<m<<"\033[0m"<<" #"<<v[i].id+1<<" hossz="<<v[i].hossz<<" ar="<<v[i].ar<<endl;
		if (v[i].hossz>m) continue;
		try {
			auto res = lefed(m-v[i].hossz, l+1, i+1);
			cerr<<"\033[32m"; fe(i,0,l) cerr<<">"; cerr<<" "<<m<<"\033[0m"<<" #"<<v[i].id+1<<" hossz="<<v[i].hossz<<" ar="<<v[i].ar<<endl;
			res[v[i]]++;
			return res;
		} catch (NOTFOUND) {
			cerr<<"\033[31m"; fe(i,0,l) cerr<<">"; cerr<<" "<<m<<"\033[0m"<<endl;
			continue;
		}
	}
	throw NOTFOUND();
}

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	cin>>n>>m; v.resize(n);
	fe (i, 0, n) {
		cin>>v[i].hossz>>v[i].ar;
		v[i].id=i;
	}
	cerr<<"Thanks!"<<endl;

	sort(v.rbegin(), v.rend());
	cerr<<"Sorted:"<<endl;
	for (auto it : v) {
		cerr<<"#"<<it.id+1<<" "<<" hossz="<<it.hossz<<" ar="<<it.ar<<endl;
	}
	cerr<<endl;

	try {
		auto res = lefed(m);
		{ int sum=0; for(auto it:res)sum+=it.first.hossz*it.second; cerr<<"sum_{hossz}="<<sum<<endl; }
		{ int sum=0; for(auto it:res)sum+=it.first.ar*it.second; cerr<<"sum_{ar}=";cout<<sum<<endl; }
		cout<<res.size()<<endl;
		for (auto it : res) {
			cerr<<"#";cout<<it.first.id+1<<" ";cerr<<"cnt=";cout<<it.second;cerr<<" hossz="<<it.first.hossz<<" ar="<<it.first.ar;cout<<endl;
		}
	} catch (NOTFOUND) {
		cout<<0;
	}

	return 0;
}
