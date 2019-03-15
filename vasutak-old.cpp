#include <bits/stdc++.h>

#define fe(i, f, t) for(int i = (f); i < (t); i++)
#define fh(i, f, t) for(int i = (f)-1; i >= (t); i--)

using namespace std;

int i, j, k, l, m, n, o, p, q, x, y, z, a, b, c;
vector<int> v;
vector<bool> reached;
int reachedCnt=0;
vector<pair<int, int>> steps;
int price=0;

struct VV {
    int price;
    int prev;
    VV() : price(numeric_limits<int>::max()), prev(-1) {}
};
vector<VV> vv;

int main()
{
    cin>>n>>k>>a>>b>>m; a--; b--; k++; //wtf?
    v.resize(n*n, numeric_limits<int>::max());
    reached.resize(n, false);
    fe(i, 0, m) {
        cin>>x>>y>>z;
        x--; y--;
        v[x*n+y]=v[y*n+x]=min(v[x*n+y], z);
    }
    cerr<<"Thanks!"<<endl;

    vv.resize(n, VV());

    int prevp=0;
    std::priority_queue<int, vector<int>, function<bool(int, int)>> q([vv](int a, int b){return vv[a].price<vv[b].price;});
    //priority_queue<int> q;
    q.push(a);
    while (q.top()!=b) {
        volatile int it = q.top(); q.pop();
        int p = vv[it].price;
        int x = it;

        cerr<<it<<endl;

        //fe(i, 0, path.size()) cerr<<"] "<<path[i]<<" "; cerr<<p<<endl;
        //if (p!=prevp) cerr<<p<<"\r"; prevp=p;

        fe(i, 0, n) {
            cerr<<">"<<i<<" "<<q.size()<<endl;
            if (v[x*n+i]==numeric_limits<int>::max()) continue;
            if (vv[i].price!=numeric_limits<int>::max()) q.push(i);
            /*
            bool bad = false;
            fe(f, 0, v.size()) {
                if (v[j]==i) {
                    bad = true;
                    break;
                }
            }
            if (bad) continue;
            */
            if (p+v[x*n+i]<vv[i].price) {
                vv[i].prev=it;
                vv[i].price=p+v[x*n+i];
            }
        }
    }
    cerr<<"Dijkstra done."<<endl;

    vector<int> path(1, b);
    while(path.back()!=a) {
        path.push_back(vv[path.back()].prev);
    }

    fh(i, path.size(), 1) {
        const int a = path[i];
        const int b = path[i-1];

        steps.push_back({a, b});
        reached[a]=reached[b]=true; reachedCnt+=2;
        price+=v[a*n+b];
    }

    while (reachedCnt<k) {
        pair<int, int> mi={0, 0};
        int mv=numeric_limits<int>::max();

        fe(i, 0, n) {
            if (reached[i]) {
                fe (j, 0, n) {
                    if (reached[j]) continue;
                    if (v[i*n+j]<mv) {
                        mi={i, j};
                        mv=v[i*n+j];
                    }
                }
            }
        }

        steps.push_back(mi);
        price+=mv;
        reached[mi.second]=true; reachedCnt++;
    }

    cout<<price<<endl;
    cout<<steps.size()<<endl;
    fe(i, 0, steps.size()) cout<<steps[i].first+1<<" "<<steps[i].second+1<<endl;

    return 0;
}
