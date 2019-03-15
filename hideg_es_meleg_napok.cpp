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

int i, j, k, l, m, n, o, p, x, y, z;
vector<int> v;
vector<signed char> v_;

int main(){
    cin>>n; v.resize(n); v_.resize(n, 0);
    for(int i=0; i<n; i++) cin>>v[i];
    cerr<<"Thanks!"<<endl;

    for(int i=1; i<(n-1); i++){
        if (v[i-1]<v[i] && v[i+1]<v[i]) v_[i]=+1;
        if (v[i-1]>v[i] && v[i+1]>v[i]) v_[i]=-1;
    }

#ifdef DEBUG
    for (auto it : v_) {cerr<<it<<" ";} cerr<<endl;
#endif

    int cnt=0;

    for(int i=0;i<n;i++) {
        if (v_[i]!=0) {
            int sum=0;
            for (int j=i;j<n;j++) {
                if (v_[j]!=0) {
                    sum+=v_[j];
                    cerr<<i<<"-"<<j<<": "<<sum<<endl;
                    if (sum==0) { // equal + and -
                        cnt++;
                    }
                }
            }
        }
    }

    cout<<cnt<<endl;
}
