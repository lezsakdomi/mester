// Feladat: Vízitúra
// (leghosszabb út keresés)
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

struct Telepules;
int max_telepules_id=0;
vector<Telepules*> telepulesek;
set<Telepules*> lehetGyoker;
struct MelybejarRes {
	struct FullChain {
		int length;
		pair<const Telepules*, const Telepules*> leafs;
		FullChain(const Telepules* telepules1, const Telepules* telepules2, int length): length(length), leafs(telepules1, telepules2) {}
		FullChain(const Telepules* telepules): length(0), leafs(telepules, telepules) {}
		bool operator<(const FullChain& o) const { return length<o.length; }
		bool operator>(const FullChain& o) const { return length>o.length; }
		bool operator==(const FullChain& o) const { return length==o.length; }
		bool operator!=(const FullChain& o) const { return length!=o.length; }
		friend ostream& operator<<(ostream&, const FullChain&);
	} fullChain;
	struct SingleChain {
		int length;
		const Telepules* leaf;
		SingleChain(const Telepules* telepules): length(0), leaf(telepules) {}
		SingleChain operator+(pair<const Telepules*, int> p) const {
			auto result = *this;
			result.length += p.second;
			return result;
		}
		FullChain operator+(const SingleChain& o) const {
			return FullChain(this->leaf, o.leaf, this->length + o.length);
		}
		bool operator<(const SingleChain& o) const { return length<o.length; }
		bool operator>(const SingleChain& o) const { return length>o.length; }
		bool operator==(const SingleChain& o) const { return length==o.length; }
		bool operator!=(const SingleChain& o) const { return length!=o.length; }
		friend ostream& operator<<(ostream&, const SingleChain&);
	} singleChain;
	MelybejarRes(const Telepules* telepules): fullChain(telepules), singleChain(telepules) {}
	MelybejarRes(const FullChain& fullChain, const SingleChain& singleChain): fullChain(fullChain), singleChain(singleChain) {}
};
struct Telepules {
	int id;
	Telepules(int id): id(id) {
		lehetGyoker.insert(this);
	}
	map<Telepules*, int> gyerekek;
	static Telepules& byId(int id) { return *telepulesek[id]; }
	bool operator<(const Telepules& o) const { return id<o.id; }
	bool operator==(const Telepules& o) const { return id==o.id; }
	MelybejarRes melybejar(const Telepules* from=0, int level = 1) {
		fe(i,0,level)cerr<<"\033[33m>";cerr<<" #"<<id+1<<"\033[0m"<<endl;
		MelybejarRes::FullChain maxFullChain(this);
		MelybejarRes::SingleChain max1(this), max2(this);
		for (auto it: gyerekek) {
			assert(it.first);
			assert(it.first != from);
			fe(i,0,level)cerr<<"\033[34m>";cerr<<"  #"<<it.first->id+1<<" "<<it.second<<"\033[0m"<<endl;
			MelybejarRes res = it.first->melybejar(this, level+1);
			if (res.fullChain > maxFullChain) {
				maxFullChain = res.fullChain;
				fe(i,0,level)cerr<<"\033[35m>";cerr<<" #"<<id+1<<" maxFullChain="<<maxFullChain<<"\033[0m"<<endl;
			}
			if (res.singleChain+it > max1) {
				max2 = max1;
				max1 = res.singleChain+it;
				fe(i,0,level)cerr<<"\033[35m>";cerr<<" #"<<id+1<<" max1="<<max1<<" max2="<<max2<<"\033[0m"<<endl;
			}
		}
		if (max1+max2 > maxFullChain) {
			fe(i,0,level)cerr<<"\033[35m>";cerr<<" #"<<id+1<<" maxFullChain=!"<<max1+max2<<"\033[0m"<<endl;
		}
		return MelybejarRes(max(maxFullChain, max1+max2), max1);
	}
};
ostream& operator<<(ostream& os, const MelybejarRes::FullChain& fc) {
	return os<<"{"<<fc.length<<": #"<<fc.leafs.first->id+1<<"..#"<<fc.leafs.second->id+1<<"}";
}
ostream& operator<<(ostream& os, const MelybejarRes::SingleChain& sc) {
	return os<<"{"<<sc.length<<": ..#"<<sc.leaf->id+1<<"}";
}

int i, j, k, l, m, n, o, p, x, y, z;
vector<int> v;

int main(){
	cin>>n; telepulesek.resize(n);
	fv(i, telepulesek) {
		telepulesek[i] = new Telepules(max_telepules_id++);
	}
	fe (i, 0, n-1) {
		cin>>x>>y>>z;
		cerr<<"\033[32m"<<"#"<<x<<"->#"<<y<<" ("<<z<<")"<<"\033[0m"<<endl;
		telepulesek.at(y-1)->gyerekek[telepulesek.at(x-1)]=z;
		lehetGyoker.erase(telepulesek[x]);
	}
	cerr<<"Thanks!"<<endl;

	auto res = telepulesek[0]->melybejar();
	assert(res.fullChain.leafs.first && res.fullChain.leafs.second);
	cout<<res.fullChain.length<<endl;
	cout<<res.fullChain.leafs.first->id+1<<" "<<res.fullChain.leafs.second->id+1<<endl;

	return 0;
}
