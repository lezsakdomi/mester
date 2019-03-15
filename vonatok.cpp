// Feladat: Vonatok
// Lezsák Domonkos

#include <bits/stdc++.h>
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

#define int long long int

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
	int vonat; bool dir; int hol;
	int priority;
	int time2;
	Event(int time,int vonat,bool dir,int hol) : time(time),vonat(vonat),dir(dir),hol(hol),priority(max_priority++*2+(dir?0:1)), time2(time) { cerr<<"> "<<*this<<endl; }
	Event(int time,int vonat,bool dir,int hol,int time2) : time(time),vonat(vonat),dir(dir),hol(hol),priority(max_priority++*2+(dir?0:1)), time2(time2) { cerr<<"> "<<*this<<endl; }
	bool operator<(const Event& o) const { return time>o.time || (time==o.time && priority>o.priority); }
	friend std::ostream& operator<<(ostream& os,const Event& e) { return os<<e.time<<": v"<<e.vonat<<" h"<<e.hol<<" goes "<<(e.dir?"right":"left"); }
};
priority_queue<Event> events;

int i, j, k, l, m, n, o, p, x, y, z;
vector<int> ido;
vector<int> ind;
vector<bool> ind_all;
vector<int> foglalt;

#undef int
int main(){
#define int long long int
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	// Adatok beolvasása
	cin>>n>>m>>p; ido.resize(n-1); ind.resize(m); ind_all.resize(m); foglalt.resize(n-1, 0);
	fe (i, 0, n-1) {
		cin>>ido[i];
	}
	fe(i, 0, m) {
		{initi(a); ind_all[i]=!(a-1);}
		cin>>ind[i];
	}
	cerr<<"Thanks!"<<endl;

	// `i` az `ind` indexeire
	fv(i, ind) {
		/* Kezdeti esemény létrehozása
		 *   `time` = vonat indulása
		 *   `vonat` = vonat azonosítója (0-tól indexelve)
		 *   `dir` = irány (Piripócs fele megy?) (("Jobbra" halad?)) (((Nő az állomás sorszáma?)))
		 *   `hol` = induló állomás (Kukutyin = 0, Piripócs = n-1)
		 */
		events.push(Event(ind[i], i, ind_all[i], ind_all[i]?0:n-1));
	}
	cerr<<"Events generated"<<endl;

	// Események feldolgozása
	while (!events.empty()) {
		// Debug kimenet: melyik vágány meddig foglalt (barna)
		for (auto it : foglalt) cerr<<"\033[34m"<<it<<"\033[0m "; cerr<<endl;

		// Lehívjuk a következő eseményt (sorrend: `time` szerint, egyezés esetén amelyik konstruktora előbb került meghívásra) (lásd Event::operator<)
		Event e = events.top(); events.pop();
		cerr<<"] "<<e<<endl;

		try {
			int vagany=e.hol+(e.dir?0:-1), start=e.time, stop=start+ido.at(vagany);
			cerr<<"\033[35m"<<"vagany="<<vagany<<" start="<<start<<" stop="<<stop<<"\033[0m"<<endl;

			/* Új esemény létrehozása
			 *   `time` = beérkezés + várakozás
			 *   `vonat` = (marad)
			 *   `dir` = (marad)
			 *   `hol` = Eggyel léptetve (`dir`től függően +1/-1)
			 *   `time2` = valódi beérkezés
			 */
			Event e2(stop+p, e.vonat, e.dir, e.hol+(e.dir?1:-1), stop);

			// Ha úgy tűnik, a vágány foglalt lenne (más vonat később érkezik, mint ez elindul)
			if (foglalt[vagany]>start) {
				// Késleltetjük az eredeti eseményt addig, amíg az foglalt lenne
				e.time=foglalt[vagany];
				cerr<<"\033[31mRather delaying until "<<e.time<<"\033[0m"<<endl;

				// ...és visszadobjuk a prioritási sorba
				events.push(e);
			} else {
				// Beállítjuk, hogy a vágány foglalt amíg a vonat végig nem ér, majd bedobjuk az új eseményt a sorba
				foglalt[vagany]=stop;
				events.push(e2);
			}
		} catch(std::exception ex) {
			cerr<<"\033[41mE: "<<ex.what()<<"\033[0m"<<endl;
			// Ha hibát kapunk, az alighanem rossz indexelés miatt van. Ez azt jelenti, hogy a vonatunk célba ért, kiírhatjuk az eredményt (és elfelejthetjük a vonatot)
			// Az idő feltételezett `p` perc várakozást, ez a végállomáson nem kell, levonhatjuk
			cerr<<"\033[36m"; cout<<(e.dir?2:1)<<" "<<e.time2<<endl; cerr<<"\033[0m";
		}
	}

	return 0;
}
