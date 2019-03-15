// https://cdn.rawgit.com/lezsakdomi/elte-mester-data/master//Nemes%20Tiham%C3%A9r%202.%202016/2017%203.%20fordul%C3%B3/K%C3%B6rutak/feladat.pdf
// Lezsák Domonkos
//#include <bits/stdc++h>
#include <iostream>
#include <vector>
#include <set>

#define cerr if(false)cerr

using namespace std;

int n; // kereszteződések száma
int m; // utak száma

vector<set<int>> to;
set<int> instack;
set<int> onkor;

void mb(int e, vector<int> stack=vector<int>(0), int level=1) {
	for (int i=-1; i<level; i++) cerr<<'>'; cerr<<" "<<e<<endl;
	if (instack.find(e)!=instack.end()) {
		cerr<<"kör"<<' ';
		for (int i=stack.size()-1; i>=0; i--) {
			cerr<<i<<' ';
			onkor.insert(stack[i]);
			if (stack[i]==e) {
				cerr<<endl;
				return;
			}
		}
		return;
	}
	instack.insert(e); stack.push_back(e);
	for (auto it : to[e]) {
		if (it==stack[stack.size()-2]) continue;
		mb(it, stack, level+1);
	}

	/*
	if (res.find(e)!=res.end()) {
		cerr<<"körtag"<<endl;
		onkor.insert(e);
		res.erase(res.find(e));
	}
	*/

	for (int i=-1; i<level; i++) cerr<<'<'; cerr<<" "<<e<<endl;
	instack.erase(instack.find(e));
	return;
}

int main(){
	//ios_base::sync_with_stdio(false);
	cin>>n>>m;
	to.resize(n+1, set<int>());
	for (int i=0; i<m; i++) {
		int x, y;
		cin>>x>>y;
		to[x].insert(y);
		to[y].insert(x);
	}
	cerr<<"Thanks"<<endl;
	
	mb(1);
	cerr<<"FINE"<<endl<<endl;

	cout<<(n-onkor.size())<<endl;
	for (int i=1; i<=n; i++) if (onkor.find(i)==onkor.end()) cout<<i<<' '; cout<<endl;
}
