// https://github.com/lezsakdomi/elte-mester-data/blob/master/Rekurz%C3%ADv%20kisz%C3%A1m%C3%ADt%C3%A1s/J%C3%A1rda%201%20%E2%80%93%201x1%2C1x2%2C1x3%20*/feladat.pdf
// Lezsák Domonkos

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id

int b(int n){
	switch (n) {
		case 1:
			return 1;

		case 2:
			return 2;

		case 3:
			return 4;

		default:
			return b(n-1)+b(n-2)+b(n-3);
	}
}

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif
	init(int, n);
	cout<<b(n);
}
