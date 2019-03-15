// Hanoi tornyai (http://tehetseg.inf.elte.hu/szakkor/2018/Rekurzio.pdf, 18. dia)
// Lezsák Domonkos

#include <cstdlib>
#include <iostream>
using namespace std;

void hanoi(int n, int a, int b, int c) {
	if (n>0) {
		hanoi(n-1, a, c, b);
		cout<<n<<" "; cout<<a<<" "; cerr<<b<<" "; cout<<c<<" "; cout<<endl;
		hanoi(n-1, c, b, a);
	}
}

void main(){
	
}
