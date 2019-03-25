// Lezsák Domonkos
// IOI válogató 2016 2f4
// Mester / Haladó / Kombinatorikai algoritmusok / 24. Válogatóverseny

// Időlimit túllépés de jónak kéne lennie => hardcode!

#include <bits/stdc++.h>

#define fe(i, from, to) for(int i=(from); i<(to); i++)
#define fh(i, from, to) for(int i=(to)-1; i>=(from); i++)

using namespace std;

int i, j, k, l, m, n, o, p, x, y, z, a, b, c;
vector<int> v;

int main()
{
    cin>>n;
    v.resize(n+1);
    fe(i, 0, n) v[i]=i;
    int pos=n;
    int cnt=0;
    while(pos>=0){
        //cerr<<"] "<<pos<<" "<<v[pos]<<endl;
        if (pos==n) {
            pos--;

            bool good=true;
            fe(i, 1, n-1) {
                if ( (v[i-1]<v[i]) == (v[i]<v[i+1]) ) {
                    good=false;
                    break;
                }
            }

            fe(i, 0, n) cerr<<v[i]; cerr<<(good?" OK":" BAD")<<endl;

            if (good) cnt++;
            continue;
        }

        bool bad=true; // trigger at least one run
        while (bad) {
            v[pos]++;
            if (v[pos]==n) break;
            bad=false;
            fe(i, 0, pos){ // should not trigger if v[pos]==n
                if (v[pos]==v[i]) {
                    bad=true;
                }
            }
        }

        //cerr<<"    "<<v[pos]<<endl;

        if (v[pos]==n) pos--;
        else v[++pos]=-1;
    }

    cout<<cnt<<endl;
    return 0;
}
