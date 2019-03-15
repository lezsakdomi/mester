// 3xN-es járda kövezése 1x2-es téglákkal
// http://tehetseg.inf.elte.hu/szakkor/2018/Rekurzio.pdf 58.dia
// Lezsák Domonkos

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id

map<int, int> ta;

int t(int n) {
	if (n%2==1) return 0;
	switch (n) {
		case 0:
		case 1:
			return 0;
		case 2:
			return 3;
		default:
			if (ta.find(n)==ta.end())
				ta[n]=3*t(n-2);
			return ta[n];
	}
}

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif

	init(int, n);
	cout<<t(n);
}
