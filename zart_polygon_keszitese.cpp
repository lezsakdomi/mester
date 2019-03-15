// Haladó/Geometriai/mintafeladat
// https://github.com/lezsakdomi/elte-mester-data/blob/master/Geometriai%20algoritmusok/Z%C3%A1rt%20poligon%20k%C3%A9sz%C3%ADt%C3%A9se%20**/feladat.pdf
// Lezsák Domonkos
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id
#define initi(id) int id; cin>>id
#define fe(id, from, to) for (int id=from; id<to; i++)
#define fh(id, to, from) for (int id=from-1; id>=to; i--)

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}



struct P {
	int x;
	int y;
	int id;
	static int _ID;
	P(int x, int y): x(x), y(y), id(++_ID) {}
	P(){}
	float atan(P o = P(0, 0)) { return ::atan( (float)(o.x+x)/(o.y+y) ); }
};
int P::_ID=0;

struct E {
	P *o, *p;
	E(P* o, P* p): o(o), p(p) {}
	float atan() { return p->atan(*o); }
	P vec() { return P(p->x-o->x, p->y-o->y); }
	int rel(E e) {
		assert(e.o==o);
		return vec().x*e.vec().y-vec().y*e.vec().x;
	}
	int hossz() {
		return sqrt(vec().x*vec().x+vec().y*vec().y);
	}
	bool kozelebb(E e) {
		assert(e.o==o);
		return hossz()<e.hossz();
	}
	bool operator==(E e) { return rel(e)==0; }
	bool operator<(E e) { return rel(e)<0; }
};

P v[100000];

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif

	initi(n);
	fe(i, 0, n) {
		initi(x);
		initi(y);
		v[i]=P(x, y);
	}


	P* q=v;
	fe(i, 0, n) {
		if ( v[i].x < q->x || ( v[i].x == q->x && v[i].y < q->y ) )
			q=v+i;
	}
	swap(*q, v[0]); q=v;
	cerr<<"q=("<<q->x<<","<<q->y<<")"<<endl;

	sort(v+1, v+n, [q](P& a, P& b){
		return E(q, &a) < E(q, &b) || (E(q, &a)==E(q, &b) && E(q, &a).kozelebb(E(q, &b)));
	});
	for (auto p=v; p!=v+n; p++) {
		cerr<<"sorted> ("<<p->x<<","<<p->y<<") #"<<p->id;
		if (E(q, p)<E(q, p+1)) cerr<<"\t"<<E(q, p).rel(E(q, p+1));
		cerr<<endl;
	} cerr<<endl;

	int j;
	for (j=n-1; E(q, v+j-1)==E(q, v+n-1); j--);
	cerr<<"j="<<j<<endl;

	fe(i, 0, j) cout<<v[i].id<<" "; cerr<<endl;
	fh(i, j, n) cout<<v[i].id<<" "; cout<<endl;
}
