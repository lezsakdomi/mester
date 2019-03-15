// https://cdn.rawgit.com/lezsakdomi/elte-mester-data/master//Moh%C3%B3%20algoritmusok/ABC%20L%C3%A1dapakol%C3%A1s%20*/feladat.pdf
// Lezsák Domonkos
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

#define init(type, id) type id; cin>>id
#define initi(id) int id; cin>>id
#define fe(id, from, to) for (int id=from; id<to; id++)
#define f(id, from, to) for (int id=from; id<to; id++)
#define fh(id, to, from) for (int id=from-1; id>=to; id--)

int main(){
#ifndef DEBUG
	ios_base::sync_with_stdio(false);
#endif

	initi(n);
	init(string, s);
	
	{
		vector<vector<bool>> v;
		v.reserve(n);
		fe(i, 0, n) {
			v.push_back(vector<bool>('C'-s[i], false));
		}

		{
			int k=n;
			fe(i, 0, n) {
				cerr<<"> #"<<i<<" ("<<s[i]<<")"<<endl;
				fe(j, i+1, n) {
					cerr<<">>  #"<<j<<endl;
					if (v[j].size()>v[i].size() && !v[j][v[i].size()]) {
						f(k, 0, (int)v[i].size()) {
							if (v[i][k] && v[j][k]) goto continj;
						}
						cerr<<">>> #"<<j<<endl;
						v[j][v[i].size()] = true;
						f(k, 0, (int)v[i].size()) {
							v[j][k] = v[i][k]||v[j][k];
						}
						k--;
						break;
					}
					continj:;
				}
			}
			cout<<k;
		}
	}
}
